#include "api.h"

#include "../utils.h"

void implType(Napi::Object exports)
{
    auto env = exports.Env();

    exports["getTypeSpelling"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getTypeSpelling, unwrap<CXType>(info[0]));
            auto ret = Napi::String::New(info.Env(), getLib(info.Env())->call_clang_func(clang_getCString, result));
            getLib(info.Env())->call_clang_func(clang_disposeString, result);
            return ret;
        },
        "nodeClang.getTypeSpelling");

    //
}
