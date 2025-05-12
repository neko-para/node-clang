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

    nc_getter std::string getFileName();
    nc_getter Napi::Date getFileTime();
    nc_getter std::optional<std::array<unsigned long long, 3>> getFileUniqueID();
    nc_method bool equal(ConvertRef<File> file);
    nc_getter std::string getRealPathName();

    nc_method bool isMultipleIncludeGuarded(ConvertRef<TranslationUnit> tu);
    nc_method std::optional<std::string> getFileContents(ConvertRef<TranslationUnit> tu);
    nc_method ConvertReturn<SourceLocation> getLocation(ConvertRef<TranslationUnit> tu, unsigned line, unsigned column);
    nc_method_as(getLocation) ConvertReturn<SourceLocation> getLocationForOffset(ConvertRef<TranslationUnit> tu, unsigned offset);

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        CXFile data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

