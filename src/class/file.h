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

    std::string getFileName();
    Napi::Date getFileTime();
    std::optional<std::array<unsigned long long, 3>> getFileUniqueID();
    bool equal(ConvertRef<File> file);
    std::string getRealPathName();

    bool isMultipleIncludeGuarded();
    std::optional<std::string> getFileContents();

    std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        Napi::ObjectReference tu;
        CXFile data {};
    };

    std::shared_ptr<State> state {};
};

