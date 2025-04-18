#include "translation_unit.h"

#include "../loader/clang.h"
#include "instance.h"
#include "clang-c/Index.h"
#include <cstdint>
#include <iostream>
#include <memory>

Napi::Function TranslationUnit::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CTranslationUnit",
        {
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &TranslationUnit::dispatcher<"nodejs inspect", &TranslationUnit::nodejsInspect>),
        });
    Instance::get(env).translationUnitConstructor = Napi::Persistent(func);
    return func;
}

TranslationUnit::TranslationUnit(const Napi::CallbackInfo& info)
    : WrapBase<TranslationUnit>(info)
    , state(std::make_shared<State>(Env()))
{
}

std::string TranslationUnit::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    if (state->data) {
        return std::format("CTranslationUnit {{ {:#018x} }}", reinterpret_cast<uintptr_t>(state->data));
    }
    else {
        return "CTranslationUnit { nullptr }";
    }
}

TranslationUnit::State::~State()
{
    if (data) {
        Instance::get(env).library->disposeTranslationUnit(data);
    }
}
