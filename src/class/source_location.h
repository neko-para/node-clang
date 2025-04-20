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

    bool isInSystemHeader();

    std::tuple<ConvertReturn<File>, unsigned, unsigned, unsigned> getExpansionLocation();
    std::tuple<std::string, unsigned, unsigned> getPresumedLocation();

    std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::ObjectReference tu;
        CXSourceLocation data {};
    };

    std::shared_ptr<State> state {};
};

