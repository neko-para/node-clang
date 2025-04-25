#pragma once

#include <memory>
#include <string>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"
#include "class/translation_unit.h"
#include "class/types.h"

struct [[clang::annotate("class")]] IndexOptions : public WrapBase<IndexOptions>
{
    static Napi::Function Init(Napi::Env env);

    IndexOptions(const Napi::CallbackInfo& info);

    [[clang::annotate("getter")]] unsigned getSize();
    [[clang::annotate("setter")]] void setSize(unsigned value);

    [[clang::annotate("getter")]] bool getThreadBackgroundPriorityForIndexing();
    [[clang::annotate("setter")]] void setThreadBackgroundPriorityForIndexing(bool value);

    [[clang::annotate("getter")]] bool getThreadBackgroundPriorityForEditing();
    [[clang::annotate("setter")]] void setThreadBackgroundPriorityForEditing(bool value);

    [[clang::annotate("getter")]] bool getExcludeDeclarationsFromPCH();
    [[clang::annotate("setter")]] void setExcludeDeclarationsFromPCH(bool value);

    [[clang::annotate("getter")]] bool getDisplayDiagnostics();
    [[clang::annotate("setter")]] void setDisplayDiagnostics(bool value);

    [[clang::annotate("getter")]] bool getStorePreamblesInMemory();
    [[clang::annotate("setter")]] void setStorePreamblesInMemory(bool value);

    [[clang::annotate("getter")]] std::optional<std::string> getPreambleStoragePath();
    [[clang::annotate("setter")]] void setPreambleStoragePath(std::optional<std::string> value);

    [[clang::annotate("getter")]] std::optional<std::string> getInvocationEmissionPath();
    [[clang::annotate("setter")]] void setInvocationEmissionPath(std::optional<std::string> value);

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

    [[clang::annotate("method")]] static std::optional<ConvertReturn<Index>>
        create(Napi::Env env, bool excludeDeclarationsFromPCH, bool displayDiagnostics);
    [[clang::annotate("method:create")]] static std::optional<ConvertReturn<Index>>
        createIndexWithOptions(Napi::Env env, ConvertRef<IndexOptions> options);
    [[clang::annotate("getter")]] unsigned getGlobalOptions();

    [[clang::annotate("method")]] std::optional<ConvertReturn<TranslationUnit>> createTranslationUnitFromSourceFile(
        std::string source_filename,
        std::vector<std::string> clang_command_line_args,
        std::vector<UnsavedFile> unsaved_files);
    [[clang::annotate("method")]] std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>>
        createTranslationUnit(std::string ast_filename);
    [[clang::annotate("method")]] std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>>
        parseTranslationUnit(
            std::string source_filename,
            std::vector<std::string> clang_command_line_args,
            std::vector<UnsavedFile> unsaved_files,
            unsigned options);
    [[clang::annotate("method")]] std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>>
        parseTranslationUnitFullArgv(
            std::string source_filename,
            std::vector<std::string> clang_command_line_args,
            std::vector<UnsavedFile> unsaved_files,
            unsigned options);

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

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

