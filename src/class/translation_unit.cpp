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
            InstanceAccessor("spelling", &TranslationUnit::dispatcher<"get spelling", &TranslationUnit::getSpelling>, nullptr),
            InstanceMethod("reparse", &TranslationUnit::dispatcher<"reparse", &TranslationUnit::reparse>),
            InstanceAccessor("cursor", &TranslationUnit::dispatcher<"get cursor", &TranslationUnit::getCursor>, nullptr),

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

std::string TranslationUnit::getSpelling()
{
    return getStr(library()->getTranslationUnitSpelling(state->data));
}

int TranslationUnit::reparse(std::vector<UnsavedFile> unsaved_files, unsigned options)
{
    std::vector<CXUnsavedFile> unsaves;

    for (const auto& unsave : unsaved_files) {
        unsaves.push_back(
            {
                std::get<0>(unsave).c_str(),
                std::get<1>(unsave).c_str(),
                std::get<2>(unsave),
            });
    }
    return library()->reparseTranslationUnit(state->data, unsaves.size(), unsaves.data(), options);
}

ConvertReturn<Cursor> TranslationUnit::getCursor()
{
    auto obj = instance().cursorConstructor.New({});
    auto cst = Napi::ObjectWrap<Cursor>::Unwrap(obj)->state;
    cst->tu = Napi::Persistent(this->Value());
    cst->data = library()->getTranslationUnitCursor(state->data);
    return { obj };
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
