#include "class/index.h"

#include <cstdint>
#include <memory>

#include "class/instance.h"
#include "class/translation_unit.h"
#include "loader/clang.h"

IndexOptions::IndexOptions(const Napi::CallbackInfo& info)
    : WrapBase<IndexOptions>(info)
    , state(std::make_shared<State>())
{
}

unsigned IndexOptions::getSize()
{
    return state->data.Size;
}

void IndexOptions::setSize(unsigned value)
{
    state->data.Size = value;
}

bool IndexOptions::getThreadBackgroundPriorityForIndexing()
{
    return state->data.ThreadBackgroundPriorityForIndexing;
}

void IndexOptions::setThreadBackgroundPriorityForIndexing(bool value)
{
    state->data.ThreadBackgroundPriorityForIndexing = value ? CXGlobalOpt_ThreadBackgroundPriorityForIndexing : 0;
}

bool IndexOptions::getThreadBackgroundPriorityForEditing()
{
    return state->data.ThreadBackgroundPriorityForEditing;
}

void IndexOptions::setThreadBackgroundPriorityForEditing(bool value)
{
    state->data.ThreadBackgroundPriorityForEditing = value ? CXGlobalOpt_ThreadBackgroundPriorityForEditing : 0;
}

bool IndexOptions::getExcludeDeclarationsFromPCH()
{
    return state->data.ExcludeDeclarationsFromPCH;
}

void IndexOptions::setExcludeDeclarationsFromPCH(bool value)
{
    state->data.ExcludeDeclarationsFromPCH = value ? 1 : 0;
}

bool IndexOptions::getDisplayDiagnostics()
{
    return state->data.DisplayDiagnostics;
}

void IndexOptions::setDisplayDiagnostics(bool value)
{
    state->data.DisplayDiagnostics = value ? 1 : 0;
}

bool IndexOptions::getStorePreamblesInMemory()
{
    return state->data.StorePreamblesInMemory;
}

void IndexOptions::setStorePreamblesInMemory(bool value)
{
    state->data.StorePreamblesInMemory = value ? 1 : 0;
}

std::optional<std::string> IndexOptions::getPreambleStoragePath()
{
    return state->__PreambleStoragePath;
}

void IndexOptions::setPreambleStoragePath(std::optional<std::string> value)
{
    state->__PreambleStoragePath = value;
}

std::optional<std::string> IndexOptions::getInvocationEmissionPath()
{
    return state->__InvocationEmissionPath;
}

void IndexOptions::setInvocationEmissionPath(std::optional<std::string> value)
{
    state->__InvocationEmissionPath = value;
}

Index::Index(const Napi::CallbackInfo& info)
    : WrapBase<Index>(info)
    , state(std::make_shared<State>(Env()))
{
}

std::optional<ConvertReturn<Index>> Index::create(Napi::Env env, bool excludeDeclarationsFromPCH, bool displayDiagnostics)
{
    auto data = Instance::get(env).library->createIndex(excludeDeclarationsFromPCH, displayDiagnostics);
    if (!data) {
        return std::nullopt;
    }
    auto [state, obj] = Index::construct(env);
    state->data = data;
    return ConvertReturn<Index> { obj };
}

std::optional<ConvertReturn<Index>> Index::createIndexWithOptions(Napi::Env env, ConvertRef<IndexOptions> options)
{
    options.data->state->__flush_pointer();
    auto data = Instance::get(env).library->createIndexWithOptions(&options.data->state->data);
    if (!data) {
        return std::nullopt;
    }
    auto [state, obj] = Index::construct(env);
    state->data = data;
    return ConvertReturn<Index> { obj };
}

unsigned Index::getGlobalOptions()
{
    return library()->CXIndex_getGlobalOptions(state->data);
}

std::optional<ConvertReturn<TranslationUnit>> Index::createTranslationUnitFromSourceFile(
    std::string source_filename,
    std::vector<std::string> clang_command_line_args,
    std::vector<UnsavedFile> unsaved_files)
{
    std::vector<const char*> args;
    std::vector<CXUnsavedFile> unsaves;

    for (const auto& arg : clang_command_line_args) {
        args.push_back(arg.c_str());
    }

    for (const auto& unsave : unsaved_files) {
        unsaves.push_back(
            {
                std::get<0>(unsave).c_str(),
                std::get<1>(unsave).c_str(),
                std::get<2>(unsave),
            });
    }

    auto tu = library()->createTranslationUnitFromSourceFile(
        state->data,
        source_filename.c_str(),
        args.size(),
        args.data(),
        unsaves.size(),
        unsaves.data());
    if (!tu) {
        return std::nullopt;
    }

    auto [state, obj] = TranslationUnit::construct(Env());
    state->data = tu;
    return ConvertReturn<TranslationUnit> { obj };
}

std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>>
    Index::createTranslationUnit(std::string ast_filename)
{
    CXTranslationUnit tu = nullptr;
    auto err = library()->createTranslationUnit2(state->data, ast_filename.c_str(), &tu);
    if (err != CXError_Success) {
        return std::tuple<ConvertNull, int>({}, err);
    }

    auto [state, obj] = TranslationUnit::construct(Env());
    state->data = tu;
    return std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>({ obj }, {});
}

std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>> Index::parseTranslationUnit(
    std::string source_filename,
    std::vector<std::string> clang_command_line_args,
    std::vector<UnsavedFile> unsaved_files,
    unsigned options)
{
    std::vector<const char*> args;
    std::vector<CXUnsavedFile> unsaves;

    for (const auto& arg : clang_command_line_args) {
        args.push_back(arg.c_str());
    }

    for (const auto& unsave : unsaved_files) {
        unsaves.push_back(
            {
                std::get<0>(unsave).c_str(),
                std::get<1>(unsave).c_str(),
                std::get<2>(unsave),
            });
    }

    CXTranslationUnit tu = nullptr;
    auto err = library()->parseTranslationUnit2(
        state->data,
        source_filename.c_str(),
        args.data(),
        args.size(),
        unsaves.data(),
        unsaves.size(),
        options,
        &tu);
    if (!tu) {
        return std::tuple<ConvertNull, int>({}, err);
    }

    auto [state, obj] = TranslationUnit::construct(Env());
    state->data = tu;
    return std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>({ obj }, {});
}

std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>> Index::parseTranslationUnitFullArgv(
    std::string source_filename,
    std::vector<std::string> clang_command_line_args,
    std::vector<UnsavedFile> unsaved_files,
    unsigned options)
{
    std::vector<const char*> args;
    std::vector<CXUnsavedFile> unsaves;

    for (const auto& arg : clang_command_line_args) {
        args.push_back(arg.c_str());
    }

    for (const auto& unsave : unsaved_files) {
        unsaves.push_back(
            {
                std::get<0>(unsave).c_str(),
                std::get<1>(unsave).c_str(),
                std::get<2>(unsave),
            });
    }

    CXTranslationUnit tu = nullptr;
    auto err = library()->parseTranslationUnit2FullArgv(
        state->data,
        source_filename.c_str(),
        args.data(),
        args.size(),
        unsaves.data(),
        unsaves.size(),
        options,
        &tu);
    if (!tu) {
        return std::tuple<ConvertNull, int>({}, err);
    }

    auto [state, obj] = TranslationUnit::construct(Env());
    state->data = tu;
    return std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>({ obj }, {});
}

std::string Index::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    if (state->data) {
        return std::format("CIndex {{ {:#018x} }}", reinterpret_cast<uintptr_t>(state->data));
    }
    else {
        return "CIndex { nullptr }";
    }
}

Index::State::~State()
{
    if (data) {
        Instance::get(env).library->disposeIndex(data);
    }
}
