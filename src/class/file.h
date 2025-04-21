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

    [[clang::annotate("getter")]] bool isMultipleIncludeGuarded();
    [[clang::annotate("getter")]] std::optional<std::string> getFileContents();

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::ObjectReference tu;
        CXFile data {};
    };

    std::shared_ptr<State> state {};
};

