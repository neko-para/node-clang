#include "clang-c/Index.h"
#include "api.h"

#include "../utils.h"

void implIndex(Napi::Object exports)
{
    auto env = exports.Env();

    exports["createIndex"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto index = getLib(info.Env())->call_clang_func(clang_createIndex, toBool(info[0]), toBool(info[1]));
            if (!index) {
                return info.Env().Null();
            }
            else {
                return wrapIndex(info.Env(), index);
            }
        },
        "nodeClang.createIndex");

    exports["createIndexWithOptions"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto opt_obj = info[0].As<Napi::Object>();

            auto PreambleStoragePath = toStr(opt_obj["PreambleStoragePath"]);
            auto InvocationEmissionPath = toStr(opt_obj["InvocationEmissionPath"]);
            CXIndexOptions opt = {
                toU32(opt_obj["Size"]),
                toU8(opt_obj["ThreadBackgroundPriorityForIndexing"]),
                toU8(opt_obj["ThreadBackgroundPriorityForEditing"]),
                toBool(opt_obj["ExcludeDeclarationsFromPCH"]),
                toBool(opt_obj["DisplayDiagnostics"]),
                toBool(opt_obj["StorePreamblesInMemory"]),
                PreambleStoragePath.c_str(),
                InvocationEmissionPath.c_str(),
            };

            auto index = getLib(info.Env())->call_clang_func(clang_createIndexWithOptions, &opt);
            if (!index) {
                return info.Env().Null();
            }
            else {
                return wrapIndex(info.Env(), index);
            }
        },
        "nodeClang.createIndexWithOptions");

    exports["CXIndex_getGlobalOptions"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto opt = getLib(info.Env())->call_clang_func(clang_CXIndex_getGlobalOptions, unwrapPtr<CXIndex>(info[0]));
            return Napi::Number::New(info.Env(), opt);
        },
        "nodeClang.CXIndex_getGlobalOptions");

    //
}
