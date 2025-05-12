#pragma once

#include <memory>
#include <string>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"
#include "class/translation_unit.h"

struct [[clang::annotate("class")]] IndexOptions : public WrapBase<IndexOptions>
{
    static Napi::Function Init(Napi::Env env);

    IndexOptions(const Napi::CallbackInfo& info);

    nc_getter unsigned getSize();
    nc_setter void setSize(unsigned value);

    nc_getter bool getThreadBackgroundPriorityForIndexing();
    nc_setter void setThreadBackgroundPriorityForIndexing(bool value);

    nc_getter bool getThreadBackgroundPriorityForEditing();
    nc_setter void setThreadBackgroundPriorityForEditing(bool value);

    nc_getter bool getExcludeDeclarationsFromPCH();
    nc_setter void setExcludeDeclarationsFromPCH(bool value);

    nc_getter bool getDisplayDiagnostics();
    nc_setter void setDisplayDiagnostics(bool value);

    nc_getter bool getStorePreamblesInMemory();
    nc_setter void setStorePreamblesInMemory(bool value);

    nc_getter std::optional<std::string> getPreambleStoragePath();
    nc_setter void setPreambleStoragePath(std::optional<std::string> value);

    nc_getter std::optional<std::string> getInvocationEmissionPath();
    nc_setter void setInvocationEmissionPath(std::optional<std::string> value);

    struct State
    {
        CXIndexOptions data {};
        std::optional<std::string> __PreambleStoragePath;
        std::optional<std::string> __InvocationEmissionPath;

        void __flush_pointer()
        {
            data.PreambleStoragePath = __PreambleStoragePath ? __PreambleStoragePath->c_str() : nullptr;
            data.InvocationEmissionPath = __InvocationEmissionPath ? __InvocationEmissionPath->c_str() : nullptr;
        }
    };

    std::shared_ptr<State> state {};
};

struct [[clang::annotate("class")]] Index : public WrapBase<Index>
{
    static Napi::Function Init(Napi::Env env);

    Index(const Napi::CallbackInfo& info);

    nc_method static std::optional<ConvertReturn<Index>> create(Napi::Env env, bool excludeDeclarationsFromPCH, bool displayDiagnostics);
    nc_method_as(create) static std::optional<ConvertReturn<Index>> createIndexWithOptions(Napi::Env env, ConvertRef<IndexOptions> options);
    nc_getter unsigned getGlobalOptions();

    nc_method std::optional<ConvertReturn<TranslationUnit>> createTranslationUnitFromSourceFile(
        std::string source_filename,
        std::vector<std::string> clang_command_line_args,
        std::vector<UnsavedFile> unsaved_files);
    nc_method Either<ConvertReturn<TranslationUnit>, int> createTranslationUnit(std::string ast_filename);
    nc_method Either<ConvertReturn<TranslationUnit>, int> parseTranslationUnit(
        std::string source_filename,
        std::vector<std::string> clang_command_line_args,
        std::vector<UnsavedFile> unsaved_files,
        unsigned options);
    nc_method Either<ConvertReturn<TranslationUnit>, int> parseTranslationUnitFullArgv(
        std::string source_filename,
        std::vector<std::string> clang_command_line_args,
        std::vector<UnsavedFile> unsaved_files,
        unsigned options);

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::Env env;
        CXIndex data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

