#include "class/index.h"

#include <cstdint>
#include <memory>

#include "class/instance.h"
#include "loader/clang.h"

#define BIND_GETTER_SETTER(name)                                                 \
    InstanceAccessor(                                                            \
        #name,                                                                   \
        &IndexOptions::dispatcher<"get " #name, &IndexOptions::get##name>,       \
        &IndexOptions::dispatcherSetter<"set " #name, &IndexOptions::set##name>, \
        napi_enumerable)

Napi::Function IndexOptions::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CIndexOptions",
        {
            BIND_GETTER_SETTER(Size),
            BIND_GETTER_SETTER(ThreadBackgroundPriorityForIndexing),
            BIND_GETTER_SETTER(ThreadBackgroundPriorityForEditing),
            BIND_GETTER_SETTER(ExcludeDeclarationsFromPCH),
            BIND_GETTER_SETTER(DisplayDiagnostics),
            BIND_GETTER_SETTER(StorePreamblesInMemory),
            BIND_GETTER_SETTER(PreambleStoragePath),
            BIND_GETTER_SETTER(InvocationEmissionPath),
        });
    Instance::get(env).indexOptionsConstructor = Napi::Persistent(func);
    return func;
}

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

Napi::Function Index::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CIndex",
        {
            InstanceMethod("create", &Index::dispatcher<"create", &Index::create, &Index::createIndexWithOptions>),
            InstanceAccessor("globalOptions", &Index::dispatcher<"get globalOptions", &Index::getGlobalOptions>, nullptr),
            InstanceMethod(
                "createTranslationUnitFromSourceFile",
                &Index::dispatcher<"createTranslationUnitFromSourceFile", &Index::createTranslationUnitFromSourceFile>),
            InstanceMethod("createTranslationUnit", &Index::dispatcher<"createTranslationUnit", &Index::createTranslationUnit>),
            InstanceMethod("parseTranslationUnit", &Index::dispatcher<"parseTranslationUnit", &Index::parseTranslationUnit>),
            InstanceMethod(
                "parseTranslationUnitFullArgv",
                &Index::dispatcher<"parseTranslationUnitFullArgv", &Index::parseTranslationUnitFullArgv>),

            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &Index::dispatcher<"nodejs inspect", &Index::nodejsInspect>),
        });
    Instance::get(env).indexConstructor = Napi::Persistent(func);
    return func;
}

Index::Index(const Napi::CallbackInfo& info)
    : WrapBase<Index>(info)
    , state(std::make_shared<State>(Env()))
{
}

bool Index::create(bool excludeDeclarationsFromPCH, bool displayDiagnostics)
{
    state->data = library()->createIndex(excludeDeclarationsFromPCH, displayDiagnostics);
    return !!state->data;
}

bool Index::createIndexWithOptions(ConvertRef<IndexOptions> options)
{
    options.data->state->__flush_pointer();
    state->data = library()->createIndexWithOptions(&options.data->state->data);
    return !!state->data;
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

    auto obj = instance().translationUnitConstructor.New({});
    Napi::ObjectWrap<TranslationUnit>::Unwrap(obj)->__change(tu);
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

    auto obj = instance().translationUnitConstructor.New({});
    Napi::ObjectWrap<TranslationUnit>::Unwrap(obj)->__change(tu);
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

    auto obj = instance().translationUnitConstructor.New({});
    Napi::ObjectWrap<TranslationUnit>::Unwrap(obj)->__change(tu);
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

    auto obj = instance().translationUnitConstructor.New({});
    Napi::ObjectWrap<TranslationUnit>::Unwrap(obj)->__change(tu);
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
