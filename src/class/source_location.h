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

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::ObjectReference tu;
        CXSourceLocation data {};
    };

    std::shared_ptr<State> state {};
};

