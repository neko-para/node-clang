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
                                  info[0].As<Napi::External<Deref<CXTranslationUnit>::type>>().Data(),
                                  info[1].As<Napi::External<CXFile>>().Data());
            return Napi::Boolean::New(info.Env(), !!result);
        },
        "nodeClang.isFileMultipleIncludeGuarded");

    exports["getFile"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto file = getLib(info.Env())
                            ->call_clang_func(
                                clang_getFile,
                                info[0].As<Napi::External<Deref<CXTranslationUnit>::type>>().Data(),
                                info[1].As<Napi::String>().Utf8Value().c_str());
            if (!file) {
                return info.Env().Null();
            }
            else {
                return Napi::External<Deref<CXFile>::type>::New(info.Env(), file);
            }
        },
        "nodeClang.getFile");

    exports["getFileContents"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            size_t size = 0;
            auto content = getLib(info.Env())
                               ->call_clang_func(
                                   clang_getFileContents,
                                   info[0].As<Napi::External<Deref<CXTranslationUnit>::type>>().Data(),
                                   info[1].As<Napi::External<Deref<CXFile>::type>>().Data(),
                                   &size);
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
                                    info[0].As<Napi::External<Deref<CXTranslationUnit>::type>>().Data(),
                                    info[1].As<Napi::External<Deref<CXFile>::type>>().Data(),
                                    info[2].As<Napi::Number>().Uint32Value(),
                                    info[3].As<Napi::Number>().Uint32Value());
            return wrap<CXSourceLocation>(info.Env(), location);
        },
        "nodeClang.getLocation");

    exports["getLocationForOffset"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto location = getLib(info.Env())
                                ->call_clang_func(
                                    clang_getLocationForOffset,
                                    info[0].As<Napi::External<Deref<CXTranslationUnit>::type>>().Data(),
                                    info[1].As<Napi::External<Deref<CXFile>::type>>().Data(),
                                    info[2].As<Napi::Number>().Uint32Value());
            return wrap<CXSourceLocation>(info.Env(), location);
        },
        "nodeClang.getLocationForOffset");

    //
}
