#include "class/translation_unit.h"

#include <cstdint>
#include <memory>

#include "class/file.h"
#include "class/instance.h"
#include "loader/clang.h"

Napi::Function TranslationUnit::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CTranslationUnit",
        {
            InstanceMethod("getFile", &TranslationUnit::dispatcher<"getFile", &TranslationUnit::getFile>),
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

std::optional<ConvertReturn<File>> TranslationUnit::getFile(std::string file_name)
{
    auto file = library()->getFile(state->data, file_name.c_str());
    if (!file) {
        return std::nullopt;
    }

    auto obj = instance().fileConstructor.New({});
    auto fst = Napi::ObjectWrap<File>::Unwrap(obj)->state;
    fst->tu = Napi::Persistent(Value());
    fst->data = file;
    return ConvertReturn<File> { obj };
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
