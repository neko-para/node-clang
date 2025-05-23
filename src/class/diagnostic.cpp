#include "class/diagnostic.h"

#include <memory>

#include "class/convert.h"
#include "class/instance.h"
#include "class/source_location.h"
#include "class/types.h"

Diagnostic::Diagnostic(const Napi::CallbackInfo& info)
    : WrapBase<Diagnostic>(info)
    , state(std::make_shared<State>(Env()))
{
}

std::optional<ConvertReturn<DiagnosticSet>> Diagnostic::getChildDiagnostics()
{
    auto diag = library()->getChildDiagnostics(state->data);
    if (!diag) {
        return std::nullopt;
    }
    auto [dstate, obj] = DiagnosticSet::construct(Env());
    dstate->data = diag;
    return ConvertReturn<DiagnosticSet> { obj };
}

std::string Diagnostic::format(unsigned option)
{
    return getStr(library()->formatDiagnostic(state->data, option));
}

unsigned Diagnostic::defaultDisplayOptions(Napi::Env env)
{
    return Instance::get(env).library->defaultDiagnosticDisplayOptions();
}

int Diagnostic::getSeverity()
{
    return library()->getDiagnosticSeverity(state->data);
}

ConvertReturn<SourceLocation> Diagnostic::getLocation()
{
    auto [sstate, obj] = SourceLocation::construct(Env());
    sstate->data = library()->getDiagnosticLocation(state->data);
    return { obj };
}

std::string Diagnostic::getSpelling()
{
    return getStr(library()->getDiagnosticSpelling(state->data));
}

std::tuple<std::string, std::string> Diagnostic::getOption()
{
    CXString disableOpt;
    auto opt = getStr(library()->getDiagnosticOption(state->data, &disableOpt));
    return {
        opt,
        getStr(disableOpt),
    };
}

unsigned Diagnostic::getCategory()
{
    return library()->getDiagnosticCategory(state->data);
}

std::string Diagnostic::getCategoryText()
{
    return getStr(library()->getDiagnosticCategoryText(state->data));
}

unsigned Diagnostic::getNumRanges()
{
    return library()->getDiagnosticNumRanges(state->data);
}

ConvertReturn<SourceRange> Diagnostic::getRange(unsigned index)
{
    auto [sstate, obj] = SourceRange::construct(Env());
    sstate->data = library()->getDiagnosticRange(state->data, index);
    return { obj };
}

unsigned Diagnostic::getNumFixIts()
{
    return library()->getDiagnosticNumFixIts(state->data);
}

std::tuple<std::string, ConvertReturn<SourceRange>> Diagnostic::getFixIt(unsigned index)
{
    CXSourceRange replacement;
    auto text = getStr(library()->getDiagnosticFixIt(state->data, index, &replacement));
    auto [sstate, obj] = SourceRange::construct(Env());
    sstate->data = replacement;
    return { text, { obj } };
}

std::string Diagnostic::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    return "CDiagnostic {}";
}

Diagnostic::State::~State()
{
    if (data) {
        Instance::get(env).library->disposeDiagnostic(data);
    }
}

DiagnosticSet::DiagnosticSet(const Napi::CallbackInfo& info)
    : WrapBase<DiagnosticSet>(info)
    , state(std::make_shared<State>(Env()))
{
}

unsigned DiagnosticSet::getLength()
{
    return library()->getNumDiagnosticsInSet(state->data);
}

std::optional<ConvertReturn<Diagnostic>> DiagnosticSet::getDiagnostic(unsigned index)
{
    auto diag = library()->getDiagnosticInSet(state->data, index);
    if (!diag) {
        return std::nullopt;
    }
    auto [dstate, obj] = Diagnostic::construct(Env());
    dstate->data = diag;
    return ConvertReturn<Diagnostic> { obj };
}

Either<ConvertReturn<DiagnosticSet>, std::tuple<int, std::string>> DiagnosticSet::load(Napi::Env env, std::string file)
{
    CXLoadDiag_Error err;
    CXString errStr;
    auto data = Instance::get(env).library->loadDiagnostics(file.c_str(), &err, &errStr);
    if (!data) {
        return EitherFailed<std::tuple<int, std::string>> {
            {},
            { err, getStr(env, errStr) },
        };
    }
    auto [state, obj] = DiagnosticSet::construct(env);
    state->data = data;
    state->dispose = true;
    return EitherSuccess<ConvertReturn<DiagnosticSet>> {
        { obj },
        {},
    };
}

std::string DiagnosticSet::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    return "CDiagnosticSet {}";
}

DiagnosticSet::State::~State()
{
    if (data && dispose) {
        Instance::get(env).library->disposeDiagnosticSet(data);
    }
}
