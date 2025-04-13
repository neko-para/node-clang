#pragma once

#include <clang-c/Index.h>
#include <napi.h>

#include "instance.h"

class Cursor : public WrapBase<Cursor>
{
public:
    static Napi::Function Init(Napi::Env env);

    Cursor(const Napi::CallbackInfo& info);

private:
    CXCursor data {};
};

