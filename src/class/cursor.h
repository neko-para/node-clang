#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "convert.h"
#include "instance.h"
#include "type.h"

class TranslationUnit;

struct Cursor : public WrapBase<Cursor>
{
    static Napi::Function Init(Napi::Env env);

    Cursor(const Napi::CallbackInfo& info);
    bool equal(ConvertRef<Cursor> cursor);
    bool isNull();
    unsigned getHash();
    int getKind();
    std::string getSpelling();
    ConvertReturn<TranslationUnit> getTranslateUnit();
    ConvertReturn<Type> getType();

    long long getEnumConstantDeclValue();

    bool visitChildren(Napi::Function visitor);

    std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::ObjectReference tu;
        CXCursor data {};
    };

    std::shared_ptr<State> state {};
};

