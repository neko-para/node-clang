#include "api.h"

#include "../utils.h"

void implCursor(Napi::Object exports)
{
    auto env = exports.Env();

    exports["equalCursors"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_equalCursors, unwrap<CXCursor>(info[0]), unwrap<CXCursor>(info[1]));
            return Napi::Boolean::New(info.Env(), !!result);
        },
        "nodeClang.equalCursors");

    exports["getCursorType"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getCursorType, unwrap<CXCursor>(info[0]));
            return wrap(info.Env(), result);
        },
        "nodeClang.getCursorType");

    exports["getEnumConstantDeclValue"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getEnumConstantDeclValue, unwrap<CXCursor>(info[0]));
            return Napi::BigInt::New(info.Env(), result);
        },
        "nodeClang.getEnumConstantDeclValue");

    exports["getCursorSpelling"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getCursorSpelling, unwrap<CXCursor>(info[0]));
            auto ret = Napi::String::New(info.Env(), getLib(info.Env())->call_clang_func(clang_getCString, result));
            getLib(info.Env())->call_clang_func(clang_disposeString, result);
            return ret;
        },
        "nodeClang.getCursorSpelling");

    exports["getCursorKind"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getCursorKind, unwrap<CXCursor>(info[0]));
            return Napi::Number::New(info.Env(), result);
        },
        "nodeClang.getCursorKind");

    //
}
