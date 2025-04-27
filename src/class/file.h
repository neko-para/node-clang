#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"

struct [[clang::annotate("class")]] File : public WrapBase<File>
{
    static Napi::Function Init(Napi::Env env);

    File(const Napi::CallbackInfo& info);

    [[clang::annotate("getter")]] std::string getFileName();
    [[clang::annotate("getter")]] Napi::Date getFileTime();
    [[clang::annotate("getter")]] std::optional<std::array<unsigned long long, 3>> getFileUniqueID();
    [[clang::annotate("method")]] bool equal(ConvertRef<File> file);
    [[clang::annotate("getter")]] std::string getRealPathName();

    [[clang::annotate("method")]] bool isMultipleIncludeGuarded(ConvertRef<TranslationUnit> tu);
    [[clang::annotate("method")]] std::optional<std::string> getFileContents(ConvertRef<TranslationUnit> tu);
    [[clang::annotate("method")]] ConvertReturn<SourceLocation> getLocation(ConvertRef<TranslationUnit> tu, unsigned line, unsigned column);
    [[clang::annotate("method:getLocation")]] ConvertReturn<SourceLocation>
        getLocationForOffset(ConvertRef<TranslationUnit> tu, unsigned offset);

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        CXFile data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

