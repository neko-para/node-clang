#include "api.h"

#include "../utils.h"

void implIndex(Napi::Object exports)
{
    auto env = exports.Env();

    exports["createIndex"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto index = getLib(info.Env())
                             ->call_clang_func(clang_createIndex, info[0].As<Napi::Boolean>().Value(), info[1].As<Napi::Boolean>().Value());
            if (!index) {
                return info.Env().Null();
            }
            else {
                return Napi::External<Deref<CXIndex>::type>::New(info.Env(), index, [](Napi::Env env, CXIndex data) {
                    getLib(env)->call_clang_func(clang_disposeIndex, data);
                });
            }
        },
        "nodeClang.createIndex");

    exports["createIndexWithOptions"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto opt_obj = info[0].As<Napi::Object>();

            auto PreambleStoragePath = Napi::Value(opt_obj["PreambleStoragePath"]).As<Napi::String>().Utf8Value();
            auto InvocationEmissionPath = Napi::Value(opt_obj["InvocationEmissionPath"]).As<Napi::String>().Utf8Value();
            CXIndexOptions opt = {
                Napi::Value(opt_obj["Size"]).As<Napi::Number>().Uint32Value(),
                static_cast<uint8_t>(Napi::Value(opt_obj["ThreadBackgroundPriorityForIndexing"]).As<Napi::Number>().Uint32Value()),
                static_cast<uint8_t>(Napi::Value(opt_obj["ThreadBackgroundPriorityForEditing"]).As<Napi::Number>().Uint32Value()),
                Napi::Value(opt_obj["ExcludeDeclarationsFromPCH"]).As<Napi::Boolean>().Value(),
                Napi::Value(opt_obj["DisplayDiagnostics"]).As<Napi::Boolean>().Value(),
                Napi::Value(opt_obj["StorePreamblesInMemory"]).As<Napi::Boolean>().Value(),
                PreambleStoragePath.c_str(),
                InvocationEmissionPath.c_str(),
            };

            auto index = getLib(info.Env())->call_clang_func(clang_createIndexWithOptions, &opt);
            if (!index) {
                return info.Env().Null();
            }
            else {
                return Napi::External<Deref<CXIndex>::type>::New(info.Env(), index, [](Napi::Env env, CXIndex data) {
                    getLib(env)->call_clang_func(clang_disposeIndex, data);
                });
            }
        },
        "nodeClang.createIndexWithOptions");

    exports["CXIndex_getGlobalOptions"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto opt = getLib(info.Env())
                           ->call_clang_func(clang_CXIndex_getGlobalOptions, info[0].As<Napi::External<Deref<CXIndex>::type>>().Data());
            return Napi::Number::New(info.Env(), opt);
        },
        "nodeClang.CXIndex_getGlobalOptions");

    //
}
