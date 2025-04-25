#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"

struct [[clang::annotate("class")]] Type : public WrapBase<Type>
{
    static Napi::Function Init(Napi::Env env);

    Type(const Napi::CallbackInfo& info);

    [[clang::annotate("method")]] bool isEqual(ConvertRef<Type> cursor);
    [[clang::annotate("getter")]] int getKind();
    [[clang::annotate("getter")]] std::string getKindStr();
    [[clang::annotate("getter")]] std::string getSpelling();

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::ObjectReference tu;
        CXType data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

