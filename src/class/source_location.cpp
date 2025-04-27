#include "class/source_location.h"

#include <memory>

#include "class/file.h"
#include "class/instance.h"

SourceLocation::SourceLocation(const Napi::CallbackInfo& info)
    : WrapBase<SourceLocation>(info)
    , state(std::make_shared<State>())
{
}

ConvertReturn<SourceLocation> SourceLocation::null(Napi::Env env)
{
    auto [state, obj] = SourceLocation::construct(env);
    state->data = Instance::get(env).library->getNullLocation();
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
        auto [fstate, obj] = File::construct(Env());
        fstate->data = file;
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

std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> SourceLocation::getSpellingLocation()
{
    CXFile file;
    unsigned line, column, offset;
    library()->getSpellingLocation(state->data, &file, &line, &column, &offset);
    if (file) {
        auto [fstate, obj] = File::construct(Env());
        fstate->data = file;
        return { ConvertReturn<File> { obj }, line, column, offset };
    }
    else {
        return { std::nullopt, line, column, offset };
    }
}

std::tuple<std::optional<ConvertReturn<File>>, unsigned, unsigned, unsigned> SourceLocation::getFileLocation()
{
    CXFile file;
    unsigned line, column, offset;
    library()->getFileLocation(state->data, &file, &line, &column, &offset);
    if (file) {
        auto [fstate, obj] = File::construct(Env());
        fstate->data = file;
        return { ConvertReturn<File> { obj }, line, column, offset };
    }
    else {
        return { std::nullopt, line, column, offset };
    }
}

std::string SourceLocation::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    return "CSourceLocation {}";
}

SourceRange::SourceRange(const Napi::CallbackInfo& info)
    : WrapBase<SourceRange>(info)
    , state(std::make_shared<State>())
{
}

ConvertReturn<SourceRange> SourceRange::null(Napi::Env env)
{
    auto [state, obj] = SourceRange::construct(env);
    state->data = Instance::get(env).library->getNullRange();
    return { obj };
}

ConvertReturn<SourceRange> SourceRange::create(Napi::Env env, ConvertRef<SourceLocation> begin, ConvertRef<SourceLocation> end)
{
    auto [state, obj] = SourceRange::construct(env);
    state->data = Instance::get(env).library->getRange(begin.data->state->data, end.data->state->data);
    return { obj };
}

bool SourceRange::isEqual(ConvertRef<SourceRange> rng)
{
    return library()->equalRanges(state->data, rng.data->state->data);
}

bool SourceRange::isNull()
{
    return library()->Range_isNull(state->data);
}

ConvertReturn<SourceLocation> SourceRange::getStart()
{
    auto [sstate, obj] = SourceLocation::construct(Env());
    sstate->data = library()->getRangeStart(state->data);
    return { obj };
}

ConvertReturn<SourceLocation> SourceRange::getEnd()
{
    auto [sstate, obj] = SourceLocation::construct(Env());
    sstate->data = library()->getRangeEnd(state->data);
    return { obj };
}

std::string SourceRange::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    return "CSourceRange {}";
}
