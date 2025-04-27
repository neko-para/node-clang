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

    [[clang::annotate("method")]] std::optional<ConvertReturn<File>> getFile(std::string file_name);
    [[clang::annotate("method")]] std::vector<ConvertReturn<SourceRange>> getSkippedRanges(ConvertRef<File> file);
    [[clang::annotate("getter")]] std::vector<ConvertReturn<SourceRange>> getAllSkippedRanges();
    [[clang::annotate("getter")]] unsigned getNumDiagnostics();
    [[clang::annotate("method")]] std::optional<ConvertReturn<Diagnostic>> getDiagnostic(unsigned index);
    [[clang::annotate("getter")]] std::optional<ConvertReturn<DiagnosticSet>> getDiagnosticSet();
    [[clang::annotate("getter")]] std::string getSpelling();
    [[clang::annotate("method")]] static unsigned defaultEditingOptions(Napi::Env env);
    [[clang::annotate("getter")]] unsigned getDefaultSaveOptions();
    [[clang::annotate("method")]] int save(std::string file_name, unsigned options);
    [[clang::annotate("method")]] bool suspend();
    [[clang::annotate("getter")]] unsigned getDefaultReparseOptions();
    [[clang::annotate("method")]] int reparse(std::vector<UnsavedFile> unsaved_files, unsigned options);
    [[clang::annotate("getter")]] ConvertReturn<Cursor> getCursor();

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

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

