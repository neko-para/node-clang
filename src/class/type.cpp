#include "class/type.h"

#include <memory>

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

std::string Type::getKindStr()
{
    return getStr(library()->getTypeKindSpelling(static_cast<CXTypeKind>(getKind())));
}

std::string Type::getSpelling()
{
    return getStr(library()->getTypeSpelling(state->data));
}

std::string Type::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    auto kind = getKind();
    if (kind != CXType_Invalid) {
        return std::format("CType {{ {}({}) }}", getSpelling(), getKindStr());
    }
    else {
        return "CType { invalid }";
    }
}
