#include "class/type.h"

#include <memory>

#include "class/cursor.h"
#include "class/instance.h"

Type::Type(const Napi::CallbackInfo& info)
    : WrapBase<Type>(info)
    , state(std::make_shared<State>())
{
}

bool Type::isEqual(ConvertRef<Type> type)
{
    return library()->equalTypes(state->data, type.data->state->data);
}

int Type::getKind()
{
    return state->data.kind;
}

std::string Type::getKindSpellingImpl()
{
    return getStr(library()->getTypeKindSpelling(static_cast<CXTypeKind>(getKind())));
}

std::string Type::getSpelling()
{
    return getStr(library()->getTypeSpelling(state->data));
}

ConvertReturn<Type> Type::canonicalType()
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->getCanonicalType(state->data);
    return { obj };
}

bool Type::isConstQualifiedType()
{
    return library()->isConstQualifiedType(state->data);
}

bool Type::isVolatileQualifiedType()
{
    return library()->isVolatileQualifiedType(state->data);
}

bool Type::isRestrictQualifiedType()
{
    return library()->isRestrictQualifiedType(state->data);
}

unsigned Type::getAddressSpace()
{
    return library()->getAddressSpace(state->data);
}

std::string Type::getTypedefName()
{
    return getStr(library()->getTypedefName(state->data));
}

ConvertReturn<Type> Type::getPointeeType()
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->getPointeeType(state->data);
    return { obj };
}

ConvertReturn<Type> Type::getUnqualifiedType()
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->getUnqualifiedType(state->data);
    return { obj };
}

ConvertReturn<Type> Type::getNonReferenceType()
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->getNonReferenceType(state->data);
    return { obj };
}

ConvertReturn<Cursor> Type::getTypeDeclaration()
{
    auto [cstate, obj] = Cursor::construct(Env());
    cstate->data = library()->getTypeDeclaration(state->data);
    return { obj };
}

std::string Type::getObjCEncoding()
{
    return getStr(library()->Type_getObjCEncoding(state->data));
}

std::string Type::getKindSpelling(Napi::Env env, int kind)
{
    return getStr(env, Instance::get(env).library->getTypeKindSpelling(static_cast<CXTypeKind>(kind)));
}

int Type::getFunctionTypeCallingConv()
{
    return library()->getFunctionTypeCallingConv(state->data);
}

ConvertReturn<Type> Type::getResultType()
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->getResultType(state->data);
    return { obj };
}

int Type::getExceptionSpecificationType()
{
    return library()->getExceptionSpecificationType(state->data);
}

std::optional<unsigned> Type::getNumArgTypes()
{
    auto res = library()->getNumArgTypes(state->data);
    if (res == -1) {
        return std::nullopt;
    }
    return res;
}

ConvertReturn<Type> Type::getArgType(unsigned index)
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->getArgType(state->data, index);
    return { obj };
}

ConvertReturn<Type> Type::getObjCObjectBaseType()
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->Type_getObjCObjectBaseType(state->data);
    return { obj };
}

unsigned Type::getNumObjCProtocolRefs()
{
    return library()->Type_getNumObjCProtocolRefs(state->data);
}

ConvertReturn<Cursor> Type::getObjCProtocolDecl(unsigned index)
{
    auto [cstate, obj] = Cursor::construct(Env());
    cstate->data = library()->Type_getObjCProtocolDecl(state->data, index);
    return { obj };
}

unsigned Type::getNumObjCTypeArgs()
{
    return library()->Type_getNumObjCTypeArgs(state->data);
}

ConvertReturn<Type> Type::getObjCTypeArg(unsigned index)
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->Type_getObjCTypeArg(state->data, index);
    return { obj };
}

std::string Type::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    auto kind = getKind();
    if (kind != CXType_Invalid) {
        return std::format("CType {{ {}({}) }}", getSpelling(), getKindSpellingImpl());
    }
    else {
        return "CType { invalid }";
    }
}
