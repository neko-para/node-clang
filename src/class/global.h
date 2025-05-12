#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/instance.h"

struct [[clang::annotate("class")]] Global : public WrapBase<Global>
{
    static Napi::Function Init(Napi::Env env);

    using WrapBase::WrapBase;

    nc_method static unsigned long long buildSessionTimestamp(Napi::Env env);
};
