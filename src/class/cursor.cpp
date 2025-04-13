#include "cursor.h"

#include "instance.h"

Napi::Function Cursor::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(env, "CCursor", {});
    Instance::get(env).cursorConstructor = Napi::Persistent(func);
    return func;
}

Cursor::Cursor(const Napi::CallbackInfo& info)
    : WrapBase<Cursor>(info)
{
}
