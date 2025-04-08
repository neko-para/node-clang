#include "api.h"

#include "../utils.h"
#include "clang-c/CXFile.h"
#include "clang-c/CXSourceLocation.h"
#include "clang-c/Index.h"

void implTu(Napi::Object exports)
{
    auto env = exports.Env();

    exports["isFileMultipleIncludeGuarded"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())
                              ->call_clang_func(
                                  clang_isFileMultipleIncludeGuarded,
                                  unwrapPtr<CXTranslationUnit>(info[0]),
                                  unwrapPtr<CXFile>(info[1]));
            return Napi::Boolean::New(info.Env(), !!result);
        },
        "nodeClang.isFileMultipleIncludeGuarded");

    exports["getFile"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto file = getLib(info.Env())->call_clang_func(clang_getFile, unwrapPtr<CXTranslationUnit>(info[0]), toStr(info[1]).c_str());
            if (!file) {
                return info.Env().Null();
            }
            else {
                return wrapPtr(info.Env(), file);
            }
        },
        "nodeClang.getFile");

    exports["getFileContents"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            size_t size = 0;
            auto content =
                getLib(info.Env())
                    ->call_clang_func(clang_getFileContents, unwrapPtr<CXTranslationUnit>(info[0]), unwrapPtr<CXFile>(info[1]), &size);
            if (content) {
                return info.Env().Null();
            }
            else {
                return Napi::String::New(info.Env(), content, size);
            }
        },
        "nodeClang.getFileContents");

    exports["getLocation"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto location = getLib(info.Env())
                                ->call_clang_func(
                                    clang_getLocation,
                                    unwrapPtr<CXTranslationUnit>(info[0]),
                                    unwrapPtr<CXFile>(info[1]),
                                    toU32(info[2]),
                                    toU32(info[3]));
            return wrap<CXSourceLocation>(info.Env(), location);
        },
        "nodeClang.getLocation");

    exports["getLocationForOffset"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto location = getLib(info.Env())
                                ->call_clang_func(
                                    clang_getLocationForOffset,
                                    unwrapPtr<CXTranslationUnit>(info[0]),
                                    unwrapPtr<CXFile>(info[1]),
                                    toU32(info[2]));
            return wrap<CXSourceLocation>(info.Env(), location);
        },
        "nodeClang.getLocationForOffset");

    //
}
