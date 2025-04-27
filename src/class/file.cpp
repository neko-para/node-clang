#include "class/file.h"

#include <memory>

#include "class/instance.h"
#include "class/translation_unit.h"

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

bool File::isMultipleIncludeGuarded(ConvertRef<TranslationUnit> tu)
{
    return library()->isFileMultipleIncludeGuarded(tu.data->state->data, state->data);
}

std::optional<std::string> File::getFileContents(ConvertRef<TranslationUnit> tu)
{
    size_t len = 0;
    auto str = library()->getFileContents(tu.data->state->data, state->data, &len);
    if (str) {
        return std::string(str, len);
    }
    else {
        return std::nullopt;
    }
}

ConvertReturn<SourceLocation> File::getLocation(ConvertRef<TranslationUnit> tu, unsigned line, unsigned column)
{
    auto data = library()->getLocation(tu.data->state->data, state->data, line, column);
    auto [sstate, obj] = SourceLocation::construct(Env());
    sstate->data = data;
    return { obj };
}

ConvertReturn<SourceLocation> File::getLocationForOffset(ConvertRef<TranslationUnit> tu, unsigned offset)
{
    auto data = library()->getLocationForOffset(tu.data->state->data, state->data, offset);
    auto [sstate, obj] = SourceLocation::construct(Env());
    sstate->data = data;
    return { obj };
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
