#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"
#include "class/type.h"

struct TranslationUnit;

struct Cursor : public WrapBase<Cursor>
{
    static Napi::Function Init(Napi::Env env);

    Cursor(const Napi::CallbackInfo& info);

    [[clang::annotate("method")]] bool equal(ConvertRef<Cursor> cursor);
    [[clang::annotate("getter")]] bool isNull();
    [[clang::annotate("getter")]] unsigned getHash();
    [[clang::annotate("getter")]] int getKind();
    [[clang::annotate("getter")]] std::string getKindStr();
    [[clang::annotate("getter")]] std::string getSpelling();
    [[clang::annotate("getter")]] ConvertReturn<TranslationUnit> getTranslateUnit();
    [[clang::annotate("getter")]] ConvertReturn<Type> getType();

    [[clang::annotate("getter")]] long long getEnumConstantDeclValue();

    [[clang::annotate("method")]] bool visitChildren(Napi::Function visitor);

    std::string __dump();
    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::ObjectReference tu;
        CXCursor data {};
    };

    std::shared_ptr<State> state {};
};

