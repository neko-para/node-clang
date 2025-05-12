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

    nc_method bool isEqual(ConvertRef<Type> cursor);
    nc_getter int getKind();
    nc_getter_as(kindSpelling) std::string getKindSpellingImpl();
    nc_getter std::string getSpelling();
    nc_getter ConvertReturn<Type> canonicalType();
    nc_getter bool isConstQualifiedType();
    nc_getter bool isVolatileQualifiedType();
    nc_getter bool isRestrictQualifiedType();
    nc_getter unsigned getAddressSpace();
    nc_getter std::string getTypedefName();
    nc_getter ConvertReturn<Type> getPointeeType();
    nc_getter ConvertReturn<Type> getUnqualifiedType();
    nc_getter ConvertReturn<Type> getNonReferenceType();
    nc_getter ConvertReturn<Cursor> getTypeDeclaration();
    nc_getter_as(ObjCEncoding) std::string getObjCEncoding();
    nc_method static std::string getKindSpelling(Napi::Env env, int kind);
    nc_getter int getFunctionTypeCallingConv();
    nc_getter ConvertReturn<Type> getResultType();
    nc_getter int getExceptionSpecificationType();
    nc_getter std::optional<unsigned> getNumArgTypes();
    nc_method ConvertReturn<Type> getArgType(unsigned index);
    nc_getter_as(ObjCObjectBaseType) ConvertReturn<Type> getObjCObjectBaseType();
    nc_getter unsigned getNumObjCProtocolRefs();
    nc_method ConvertReturn<Cursor> getObjCProtocolDecl(unsigned index);
    nc_getter unsigned getNumObjCTypeArgs();
    nc_method ConvertReturn<Type> getObjCTypeArg(unsigned index);
    nc_getter bool isFunctionTypeVariadic();

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        CXType data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

