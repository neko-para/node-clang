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
    [[clang::annotate("getter:kindSpelling")]] std::string getKindSpellingImpl();
    [[clang::annotate("getter")]] std::string getSpelling();
    [[clang::annotate("getter")]] ConvertReturn<Type> canonicalType();
    [[clang::annotate("getter")]] bool isConstQualifiedType();
    [[clang::annotate("getter")]] bool isVolatileQualifiedType();
    [[clang::annotate("getter")]] bool isRestrictQualifiedType();
    [[clang::annotate("getter")]] unsigned getAddressSpace();
    [[clang::annotate("getter")]] std::string getTypedefName();
    [[clang::annotate("getter")]] ConvertReturn<Type> getPointeeType();
    [[clang::annotate("getter")]] ConvertReturn<Type> getUnqualifiedType();
    [[clang::annotate("getter")]] ConvertReturn<Type> getNonReferenceType();
    [[clang::annotate("getter")]] ConvertReturn<Cursor> getTypeDeclaration();
    [[clang::annotate("getter:ObjCEncoding")]] std::string getObjCEncoding();
    [[clang::annotate("method")]] static std::string getKindSpelling(Napi::Env env, int kind);
    [[clang::annotate("getter")]] int getFunctionTypeCallingConv();
    [[clang::annotate("getter")]] ConvertReturn<Type> getResultType();
    [[clang::annotate("getter")]] int getExceptionSpecificationType();

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        CXType data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

