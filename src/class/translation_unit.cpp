#include "class/translation_unit.h"

#include <algorithm>
#include <iterator>
#include <memory>

#include "class/diagnostic.h"
#include "class/file.h"
#include "class/instance.h"
#include "clang-c/Index.h"

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

    auto [fstate, obj] = File::construct(Env());
    fstate->data = file;
    return ConvertReturn<File> { obj };
}

std::vector<ConvertReturn<SourceRange>> TranslationUnit::getSkippedRanges(ConvertRef<File> file)
{
    auto lst = library()->getSkippedRanges(state->data, file.data->state->data);
    std::vector<ConvertReturn<SourceRange>> result;
    result.reserve(lst->count);
    std::transform(
        lst->ranges,
        lst->ranges + lst->count,
        std::back_insert_iterator(result),
        [&](const CXSourceRange& rng) -> ConvertReturn<SourceRange> {
            auto [sstate, obj] = SourceRange::construct(Env());
            sstate->data = rng;
            return { obj };
        });
    library()->disposeSourceRangeList(lst);
    return result;
}

std::vector<ConvertReturn<SourceRange>> TranslationUnit::getAllSkippedRanges()
{
    auto lst = library()->getAllSkippedRanges(state->data);
    std::vector<ConvertReturn<SourceRange>> result;
    result.reserve(lst->count);
    std::transform(
        lst->ranges,
        lst->ranges + lst->count,
        std::back_insert_iterator(result),
        [&](const CXSourceRange& rng) -> ConvertReturn<SourceRange> {
            auto [sstate, obj] = SourceRange::construct(Env());
            sstate->data = rng;
            return { obj };
        });
    library()->disposeSourceRangeList(lst);
    return result;
}

unsigned TranslationUnit::getNumDiagnostics()
{
    return library()->getNumDiagnostics(state->data);
}

std::optional<ConvertReturn<Diagnostic>> TranslationUnit::getDiagnostic(unsigned index)
{
    auto diag = library()->getDiagnostic(state->data, index);
    if (!diag) {
        return std::nullopt;
    }
    auto [dstate, obj] = Diagnostic::construct(Env());
    dstate->data = diag;
    return ConvertReturn<Diagnostic> { obj };
}

std::optional<ConvertReturn<DiagnosticSet>> TranslationUnit::getDiagnosticSet()
{
    auto diags = library()->getDiagnosticSetFromTU(state->data);
    if (!diags) {
        return std::nullopt;
    }
    auto [dstate, obj] = DiagnosticSet::construct(Env());
    dstate->data = diags;
    return ConvertReturn<DiagnosticSet> { obj };
}

std::string TranslationUnit::getSpelling()
{
    return getStr(library()->getTranslationUnitSpelling(state->data));
}

unsigned TranslationUnit::defaultEditingOptions(Napi::Env env)
{
    return Instance::get(env).library->defaultEditingTranslationUnitOptions();
}

unsigned TranslationUnit::getDefaultSaveOptions()
{
    return library()->defaultSaveOptions(state->data);
}

int TranslationUnit::save(std::string file_name, unsigned options)
{
    return library()->saveTranslationUnit(state->data, file_name.c_str(), options);
}

bool TranslationUnit::suspend()
{
    return library()->suspendTranslationUnit(state->data);
}

unsigned TranslationUnit::getDefaultReparseOptions()
{
    return library()->defaultReparseOptions(state->data);
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

std::vector<std::tuple<int, std::string, unsigned long>> TranslationUnit::getResourceUsage()
{
    std::vector<std::tuple<int, std::string, unsigned long>> result;
    auto usage = library()->getCXTUResourceUsage(state->data);
    result.reserve(usage.numEntries);
    std::transform(
        usage.entries,
        usage.entries + usage.numEntries,
        std::back_insert_iterator(result),
        [&](const CXTUResourceUsageEntry& entry) -> std::tuple<int, std::string, unsigned long> {
            return {
                entry.kind,
                library()->getTUResourceUsageName(entry.kind),
                entry.amount,
            };
        });
    library()->disposeCXTUResourceUsage(usage);
    return result;
}

std::tuple<std::optional<std::string>, std::optional<int>> TranslationUnit::getTargetInfo()
{
    auto info = library()->getTranslationUnitTargetInfo(state->data);

    std::optional<std::string> triple = getStr(library()->TargetInfo_getTriple(info));
    if (triple->empty()) {
        triple = std::nullopt;
    }

    std::optional<int> pointer_width = library()->TargetInfo_getPointerWidth(info);
    if (*pointer_width == -1) {
        pointer_width = std::nullopt;
    }

    return {
        triple,
        pointer_width,
    };
}

ConvertReturn<Cursor> TranslationUnit::getCursor()
{
    auto [cstate, obj] = Cursor::construct(Env());
    cstate->data = library()->getTranslationUnitCursor(state->data);
    return { obj };
}

ConvertReturn<Cursor> TranslationUnit::getCursorForLocation(ConvertRef<SourceLocation> location)
{
    auto [cstate, obj] = Cursor::construct(Env());
    cstate->data = library()->getCursor(state->data, location.data->state->data);
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
        Instance::get(env).translationUnits.erase(data);
        Instance::get(env).library->disposeTranslationUnit(data);
    }
}
