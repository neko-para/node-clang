#pragma once

#include <clang-c/Index.h>
#include <napi.h>

#include "instance.h"

class Index : public WrapBase<Index>
{
public:
    static Napi::Function Init(Napi::Env env);

    Index(const Napi::CallbackInfo& info);
    ~Index();

    void create(bool excludeDeclarationsFromPCH, bool displayDiagnostics);

    unsigned globalOptions();

private:
    CXIndex data {};
};

