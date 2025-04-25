#include "class/source_location.h"

#include <cstdint>
#include <memory>

#include "class/file.h"
#include "class/instance.h"
#include "loader/clang.h"

SourceLocation::SourceLocation(const Napi::CallbackInfo& info)
    : WrapBase<SourceLocation>(info)
    , state(std::make_shared<State>())
{
}

bool SourceLocation::isInSystemHeader()
{
    return library()->Location_isInSystemHeader(state->data);
}

std::tuple<ConvertReturn<File>, unsigned, unsigned, unsigned> SourceLocation::getExpansionLocation()
{
    CXFile file;
    unsigned line, column, offset;
    library()->getExpansionLocation(state->data, &file, &line, &column, &offset);
    auto obj = instance().fileConstructor.New({});
    auto fst = Napi::ObjectWrap<File>::Unwrap(obj)->state;
    fst->tu = Napi::Persistent(state->tu.Value());
    fst->data = file;
    return { { obj }, line, column, offset };
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
