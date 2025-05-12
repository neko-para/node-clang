#pragma once

#include <memory>
#include <string>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/cursor.h"
#include "class/file.h"
#include "class/instance.h"
#include "class/types.h"

struct [[clang::annotate("class")]] TranslationUnit : public WrapBase<TranslationUnit>
{
    static Napi::Function Init(Napi::Env env);

    TranslationUnit(const Napi::CallbackInfo& info);

    nc_method std::optional<ConvertReturn<File>> getFile(std::string file_name);
    nc_method std::vector<ConvertReturn<SourceRange>> getSkippedRanges(ConvertRef<File> file);
    nc_getter std::vector<ConvertReturn<SourceRange>> getAllSkippedRanges();
    nc_getter unsigned getNumDiagnostics();
    nc_method std::optional<ConvertReturn<Diagnostic>> getDiagnostic(unsigned index);
    nc_getter std::optional<ConvertReturn<DiagnosticSet>> getDiagnosticSet();
    nc_getter std::string getSpelling();
    nc_method static unsigned defaultEditingOptions(Napi::Env env);
    nc_getter unsigned getDefaultSaveOptions();
    nc_method int save(std::string file_name, unsigned options);
    nc_method bool suspend();
    nc_getter unsigned getDefaultReparseOptions();
    nc_method int reparse(std::vector<UnsavedFile> unsaved_files, unsigned options);
    nc_getter std::vector<std::tuple<int, std::string, unsigned long>> getResourceUsage();
    nc_getter std::tuple<std::optional<std::string>, std::optional<int>> getTargetInfo();
    nc_getter ConvertReturn<Cursor> getCursor();
    nc_method_as(getCursor) ConvertReturn<Cursor> getCursorForLocation(ConvertRef<SourceLocation> location);

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::Env env;
        CXTranslationUnit data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

