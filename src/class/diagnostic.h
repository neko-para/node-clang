#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>
#include <string>

#include "class/convert.h"
#include "class/instance.h"
#include "class/types.h"

struct [[clang::annotate("class")]] Diagnostic : public WrapBase<Diagnostic>
{
    static Napi::Function Init(Napi::Env env);

    Diagnostic(const Napi::CallbackInfo& info);

    nc_getter std::optional<ConvertReturn<DiagnosticSet>> getChildDiagnostics();

    nc_method std::string format(unsigned option);
    nc_method static unsigned defaultDisplayOptions(Napi::Env env);
    nc_getter int getSeverity();
    nc_getter ConvertReturn<SourceLocation> getLocation();
    nc_getter std::string getSpelling();
    nc_getter std::tuple<std::string, std::string> getOption();
    nc_getter unsigned getCategory();
    nc_getter std::string getCategoryText();
    nc_getter unsigned getNumRanges();
    nc_method ConvertReturn<SourceRange> getRange(unsigned index);
    nc_getter unsigned getNumFixIts();
    nc_method std::tuple<std::string, ConvertReturn<SourceRange>> getFixIt(unsigned index);

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

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

    nc_getter unsigned getLength();
    nc_method std::optional<ConvertReturn<Diagnostic>> getDiagnostic(unsigned index);

    nc_method static Either<ConvertReturn<DiagnosticSet>, std::tuple<int, std::string>> load(Napi::Env env, std::string file);

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

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

