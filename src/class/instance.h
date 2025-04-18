#pragma once

#include <format>

#include <napi.h>
#include <sstream>

#include "utils.h"

struct Library;

struct Instance
{
    Library* library {};
    Napi::FunctionReference indexOptionsConstructor;
    Napi::FunctionReference indexConstructor;
    Napi::FunctionReference translationUnitConstructor;
    Napi::FunctionReference cursorConstructor;

    static void init(Napi::Env env) { env.SetInstanceData<Instance>(new Instance); }

    static Instance& get(Napi::Env env) { return *env.GetInstanceData<Instance>(); }
};

template <auto N>
struct StringLitteral
{
    constexpr StringLitteral(const char (&str)[N]) { std::copy_n(str, N, value); }

    char value[N];
};

template <typename Type>
struct WrapBase : Napi::ObjectWrap<Type>
{
    using Napi::ObjectWrap<Type>::ObjectWrap;

    auto& instance() { return Instance::get(Napi::ObjectWrap<Type>::Env()); }

    auto library() { return instance().library; }

    template <StringLitteral name, auto... impl>
    Napi::Value dispatcher(const Napi::CallbackInfo& info)
    {
        constexpr auto func = wrap<Type, impl...>();
        std::vector<std::string> trace;
        auto result = func(static_cast<Type&>(*this), info, trace);
        if (result.has_value()) {
            return result.value();
        }
        else {
            std::ostringstream traceResult;
            for (const auto& err : trace) {
                traceResult << err << '\n';
            }
            Napi::Error::New(info.Env(), std::format("nodeClang: cannot resolve {}\n{}", name.value, traceResult.str()))
                .ThrowAsJavaScriptException();
            return info.Env().Null();
        }
    }

    template <StringLitteral name, auto... impl>
    void dispatcherSetter(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        constexpr auto func = wrapSetter<Type, impl...>();
        std::vector<std::string> trace;
        auto result = func(static_cast<Type&>(*this), info, value, trace);
        if (result.has_value()) {
            return;
        }
        else {
            std::ostringstream traceResult;
            for (const auto& err : trace) {
                traceResult << err << '\n';
            }
            Napi::Error::New(info.Env(), std::format("nodeClang: cannot resolve {}\n{}", name.value, traceResult.str()))
                .ThrowAsJavaScriptException();
            return;
        }
    }
};
