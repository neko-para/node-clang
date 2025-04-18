#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "convert.h"
#include "instance.h"

struct Type : public WrapBase<Type>
{
    static Napi::Function Init(Napi::Env env);

    Type(const Napi::CallbackInfo& info);
    bool equal(ConvertRef<Type> cursor);
    int getKind();
    std::string getKindStr();
    std::string getSpelling();

    std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::ObjectReference tu;
        CXType data {};
    };

    std::shared_ptr<State> state {};
};

