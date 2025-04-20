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

    unsigned getSize();
    void setSize(unsigned value);

    bool getThreadBackgroundPriorityForIndexing();
    void setThreadBackgroundPriorityForIndexing(bool value);

    bool getThreadBackgroundPriorityForEditing();
    void setThreadBackgroundPriorityForEditing(bool value);

    bool getExcludeDeclarationsFromPCH();
    void setExcludeDeclarationsFromPCH(bool value);

    bool getDisplayDiagnostics();
    void setDisplayDiagnostics(bool value);

    bool getStorePreamblesInMemory();
    void setStorePreamblesInMemory(bool value);

    std::optional<std::string> getPreambleStoragePath();
    void setPreambleStoragePath(std::optional<std::string> value);

    std::optional<std::string> getInvocationEmissionPath();
    void setInvocationEmissionPath(std::optional<std::string> value);

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

    bool create(bool excludeDeclarationsFromPCH, bool displayDiagnostics);
    bool createIndexWithOptions(ConvertRef<IndexOptions> options);
    unsigned getGlobalOptions();

    std::optional<ConvertReturn<TranslationUnit>> createTranslationUnitFromSourceFile(
        std::string source_filename,
        std::vector<std::string> clang_command_line_args,
        std::vector<UnsavedFile> unsaved_files);
    std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>>
        createTranslationUnit(std::string ast_filename);
    std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>> parseTranslationUnit(
        std::string source_filename,
        std::vector<std::string> clang_command_line_args,
        std::vector<UnsavedFile> unsaved_files,
        unsigned options);
    std::variant<std::tuple<ConvertReturn<TranslationUnit>, ConvertNull>, std::tuple<ConvertNull, int>> parseTranslationUnitFullArgv(
        std::string source_filename,
        std::vector<std::string> clang_command_line_args,
        std::vector<UnsavedFile> unsaved_files,
        unsigned options);

    std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::Env env;
        CXIndex data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};
};

