#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/file.h"
#include "class/instance.h"

struct [[clang::annotate("class")]] SourceLocation : public WrapBase<SourceLocation>
{
    static Napi::Function Init(Napi::Env env);

    SourceLocation(const Napi::CallbackInfo& info);

    nc_method static ConvertReturn<SourceLocation> null(Napi::Env env);

    nc_method bool isEqual(ConvertRef<SourceLocation> loc);
    nc_method bool isBefore(ConvertRef<SourceLocation> loc);
    nc_getter bool isInSystemHeader();
    nc_getter bool isFromMainFile();

    nc_getter std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> getExpansionLocation();
    nc_getter std::tuple<std::string, unsigned, unsigned> getPresumedLocation();
    nc_getter std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> getSpellingLocation();
    nc_getter std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> getFileLocation();

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        CXSourceLocation data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

struct [[clang::annotate("class")]] SourceRange : public WrapBase<SourceRange>
{
    static Napi::Function Init(Napi::Env env);

    SourceRange(const Napi::CallbackInfo& info);

    nc_method static ConvertReturn<SourceRange> null(Napi::Env env);
    nc_method static ConvertReturn<SourceRange> create(Napi::Env env, ConvertRef<SourceLocation> begin, ConvertRef<SourceLocation> end);

    nc_method bool isEqual(ConvertRef<SourceRange> rng);
    nc_getter bool isNull();

    nc_getter ConvertReturn<SourceLocation> getStart();
    nc_getter ConvertReturn<SourceLocation> getEnd();

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        CXSourceRange data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};
