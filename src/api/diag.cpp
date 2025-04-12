#include "api.h"

#include "../utils.h"
#include "clang-c/CXString.h"

void implDiag(Napi::Object exports)
{
    auto env = exports.Env();

    exports["getNumDiagnosticsInSet"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getNumDiagnosticsInSet, unwrapPtr<CXDiagnosticSet>(info[0]));
            return Napi::Number::New(info.Env(), !!result);
        },
        "nodeClang.getNumDiagnosticsInSet");

    exports["getDiagnosticInSet"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto diag = getLib(info.Env())->call_clang_func(clang_getDiagnosticInSet, unwrapPtr<CXDiagnosticSet>(info[0]), toU32(info[1]));
            return wrapDiag(info.Env(), diag);
        },
        "nodeClang.getDiagnosticInSet");

    exports["loadDiagnostics"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            CXLoadDiag_Error error;
            CXString errorString;
            auto diags = getLib(info.Env())->call_clang_func(clang_loadDiagnostics, toStr(info[0]).c_str(), &error, &errorString);
            if (!diags) {
                getLib(info.Env())->call_clang_func(clang_disposeString, errorString);
                return info.Env().Null();
            }
            auto result = Napi::Array::New(info.Env(), 3);
            result[0u] = wrapDiagSet(info.Env(), diags);
            result[1u] = Napi::Number::New(info.Env(), error);
            result[2u] = Napi::String::New(info.Env(), getLib(info.Env())->call_clang_func(clang_getCString, errorString));
            getLib(info.Env())->call_clang_func(clang_disposeString, errorString);
            return result;
        },
        "nodeClang.loadDiagnostics");

    exports["getChildDiagnostics"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto diags = getLib(info.Env())->call_clang_func(clang_getChildDiagnostics, unwrapPtr<CXDiagnostic>(info[0]));
            // no release as expected
            return wrapPtr(info.Env(), diags);
        },
        "nodeClang.getChildDiagnostics");

    exports["formatDiagnostic"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto str = getLib(info.Env())->call_clang_func(clang_formatDiagnostic, unwrapPtr<CXDiagnostic>(info[0]), toU32(info[1]));
            auto result = Napi::String::New(info.Env(), getLib(info.Env())->call_clang_func(clang_getCString, str));
            getLib(info.Env())->call_clang_func(clang_disposeString, str);
            return result;
        },
        "nodeClang.formatDiagnostic");

    exports["defaultDiagnosticDisplayOptions"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_defaultDiagnosticDisplayOptions);
            return Napi::Number::New(info.Env(), result);
        },
        "nodeClang.defaultDiagnosticDisplayOptions");

    exports["getDiagnosticSeverity"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getDiagnosticSeverity, unwrapPtr<CXDiagnostic>(info[0]));
            return Napi::Number::New(info.Env(), result);
        },
        "nodeClang.getDiagnosticSeverity");
}
