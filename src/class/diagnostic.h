#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"

struct DiagnosticSet;

struct [[clang::annotate("class")]] Diagnostic : public WrapBase<Diagnostic>
{
    static Napi::Function Init(Napi::Env env);

    Diagnostic(const Napi::CallbackInfo& info);

    [[clang::annotate("getter")]] std::optional<ConvertReturn<DiagnosticSet>> getChildDiagnostics();

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::Env env;
        CXDiagnostic data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

struct [[clang::annotate("class")]] DiagnosticSet : public WrapBase<DiagnosticSet>
{
    static Napi::Function Init(Napi::Env env);

    DiagnosticSet(const Napi::CallbackInfo& info);

    [[clang::annotate("getter")]] unsigned getLength();
    [[clang::annotate("method")]] std::optional<ConvertReturn<Diagnostic>> getDiagnostic(unsigned index);

    [[clang::annotate("method")]] static std::
        variant<std::tuple<ConvertReturn<DiagnosticSet>, ConvertNull>, std::tuple<ConvertNull, std::tuple<int, std::string>>>
        load(Napi::Env env, std::string file);

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::Env env;
        CXDiagnosticSet data {};
        bool dispose = false;

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

