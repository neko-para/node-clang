#include "class/source_location.h"

#include <memory>

#include "class/file.h"
#include "class/instance.h"
#include "loader/clang.h"

SourceLocation::SourceLocation(const Napi::CallbackInfo& info)
    : WrapBase<SourceLocation>(info)
    , state(std::make_shared<State>())
{
}

ConvertReturn<SourceLocation> SourceLocation::null(Napi::Env env)
{
    auto obj = Instance::get(env).sourceLocationConstructor.New({});
    auto sst = Napi::ObjectWrap<SourceLocation>::Unwrap(obj)->state;
    sst->data = Instance::get(env).library->getNullLocation();
    return { obj };
}

bool SourceLocation::isEqual(ConvertRef<SourceLocation> loc)
{
    return library()->equalLocations(state->data, loc.data->state->data);
}

bool SourceLocation::isBefore(ConvertRef<SourceLocation> loc)
{
    return library()->isBeforeInTranslationUnit(state->data, loc.data->state->data);
}

bool SourceLocation::isInSystemHeader()
{
    return library()->Location_isInSystemHeader(state->data);
}

bool SourceLocation::isFromMainFile()
{
    return library()->Location_isFromMainFile(state->data);
}

std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> SourceLocation::getExpansionLocation()
{
    CXFile file;
    unsigned line, column, offset;
    library()->getExpansionLocation(state->data, &file, &line, &column, &offset);
    if (file) {
        auto obj = instance().fileConstructor.New({});
        auto fst = Napi::ObjectWrap<File>::Unwrap(obj)->state;
        fst->tu = Napi::Persistent(state->tu.Value());
        fst->data = file;
        return { ConvertReturn<File> { obj }, line, column, offset };
    }
    else {
        return { std::nullopt, line, column, offset };
    }
}

std::tuple<std::string, unsigned, unsigned> SourceLocation::getPresumedLocation()
{
    CXString filename;
    unsigned line, column;
    library()->getPresumedLocation(state->data, &filename, &line, &column);
    return { getStr(filename), line, column };
}

std::string SourceLocation::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    return "CSourceLocation {}";
}
