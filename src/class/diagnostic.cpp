#include "class/diagnostic.h"

#include <memory>

#include "class/convert.h"
#include "class/instance.h"
#include "clang-c/CXDiagnostic.h"

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

std::variant<std::tuple<ConvertReturn<DiagnosticSet>, ConvertNull>, std::tuple<ConvertNull, std::tuple<int, std::string>>>
    DiagnosticSet::load(Napi::Env env, std::string file)
{
    CXLoadDiag_Error err;
    CXString errStr;
    auto data = Instance::get(env).library->loadDiagnostics(file.c_str(), &err, &errStr);
    if (!data) {
        return std::tuple<ConvertNull, std::tuple<int, std::string>> {
            {},
            { err, getStr(env, errStr) },
        };
    }
    auto [state, obj] = DiagnosticSet::construct(env);
    state->data = data;
    state->dispose = true;
    return std::tuple<ConvertReturn<DiagnosticSet>, ConvertNull> {
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
