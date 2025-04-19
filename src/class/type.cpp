#include "class/type.h"

#include <memory>

#include "class/instance.h"

Napi::Function Type::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CType",
        { InstanceMethod("equal", &Type::dispatcher<"equal", &Type::equal>),
          InstanceAccessor("kind", &Type::dispatcher<"get kind", &Type::getKind>, nullptr),
          InstanceAccessor("kindStr", &Type::dispatcher<"get kindStr", &Type::getKindStr>, nullptr),
          InstanceAccessor("spelling", &Type::dispatcher<"get spelling", &Type::getSpelling>, nullptr),

          InstanceMethod(
              Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
              &Type::dispatcher<"nodejs inspect", &Type::nodejsInspect>) });
    Instance::get(env).typeConstructor = Napi::Persistent(func);
    return func;
}

Type::Type(const Napi::CallbackInfo& info)
    : WrapBase<Type>(info)
    , state(std::make_shared<State>())
{
}

bool Type::equal(ConvertRef<Type> type)
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
