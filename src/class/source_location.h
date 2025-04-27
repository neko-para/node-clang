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

    [[clang::annotate("method")]] static ConvertReturn<SourceLocation> null(Napi::Env env);

    [[clang::annotate("method")]] bool isEqual(ConvertRef<SourceLocation> loc);
    [[clang::annotate("method")]] bool isBefore(ConvertRef<SourceLocation> loc);
    [[clang::annotate("getter")]] bool isInSystemHeader();
    [[clang::annotate("getter")]] bool isFromMainFile();

    [[clang::annotate("getter")]] std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> getExpansionLocation();
    [[clang::annotate("getter")]] std::tuple<std::string, unsigned, unsigned> getPresumedLocation();
    [[clang::annotate("getter")]] std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> getSpellingLocation();
    [[clang::annotate("getter")]] std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> getFileLocation();

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

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

    [[clang::annotate("method")]] static ConvertReturn<SourceRange> null(Napi::Env env);
    [[clang::annotate("method")]] static ConvertReturn<SourceRange>
        create(Napi::Env env, ConvertRef<SourceLocation> begin, ConvertRef<SourceLocation> end);

    [[clang::annotate("method")]] bool isEqual(ConvertRef<SourceRange> rng);
    [[clang::annotate("getter")]] bool isNull();

    [[clang::annotate("getter")]] ConvertReturn<SourceLocation> getStart();
    [[clang::annotate("getter")]] ConvertReturn<SourceLocation> getEnd();

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        CXSourceRange data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};
