#include "class/file.h"

#include <memory>

#include "class/instance.h"
#include "translation_unit.h"
#include "clang-c/CXFile.h"

Napi::Function File::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CFile",
        { InstanceAccessor("fileName", &File::dispatcher<"get fileName", &File::getFileName>, nullptr),
          InstanceAccessor("fileTime", &File::dispatcher<"get fileTime", &File::getFileTime>, nullptr),
          InstanceAccessor("fileUniqueID", &File::dispatcher<"get fileUniqueID", &File::getFileUniqueID>, nullptr),
          InstanceAccessor("fileUniqueID", &File::dispatcher<"get fileUniqueID", &File::getFileUniqueID>, nullptr),
          InstanceMethod("equal", &File::dispatcher<"equal", &File::equal>),
          InstanceAccessor("realPathName", &File::dispatcher<"get realPathName", &File::getRealPathName>, nullptr),

          InstanceAccessor(
              "isMultipleIncludeGuarded",
              &File::dispatcher<"get isMultipleIncludeGuarded", &File::isMultipleIncludeGuarded>,
              nullptr),
          InstanceAccessor("fileContents", &File::dispatcher<"get fileContents", &File::getFileContents>, nullptr),

          InstanceMethod(
              Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
              &File::dispatcher<"nodejs inspect", &File::nodejsInspect>) });
    Instance::get(env).fileConstructor = Napi::Persistent(func);
    return func;
}

File::File(const Napi::CallbackInfo& info)
    : WrapBase<File>(info)
    , state(std::make_shared<State>())
{
}

std::string File::getFileName()
{
    return getStr(library()->getFileName(state->data));
}

Napi::Date File::getFileTime()
{
    return Napi::Date::New(Env(), library()->getFileTime(state->data));
}

std::optional<std::array<unsigned long long, 3>> File::getFileUniqueID()
{
    CXFileUniqueID id;
    if (library()->getFileUniqueID(state->data, &id)) {
        return std::array<unsigned long long, 3> { id.data[0], id.data[1], id.data[2] };
    }
    else {
        return std::nullopt;
    }
}

bool File::equal(ConvertRef<File> type)
{
    return library()->File_isEqual(state->data, type.data->state->data);
}

std::string File::getRealPathName()
{
    return getStr(library()->File_tryGetRealPathName(state->data));
}

bool File::isMultipleIncludeGuarded()
{
    auto tu = Napi::ObjectWrap<TranslationUnit>::Unwrap(state->tu.Value());
    return library()->isFileMultipleIncludeGuarded(tu->state->data, state->data);
}

std::optional<std::string> File::getFileContents()
{
    auto tu = Napi::ObjectWrap<TranslationUnit>::Unwrap(state->tu.Value());
    size_t len = 0;
    auto str = library()->getFileContents(tu->state->data, state->data, &len);
    if (str) {
        return std::string(str, len);
    }
    else {
        return std::nullopt;
    }
}

std::string File::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    if (state->data) {
        auto path = getRealPathName();
        if (path.empty()) {
            path = getFileName();
        }
        return std::format("CFile {{ {} }}", path);
    }
    else {
        return "CFile { nullptr }";
    }
}
