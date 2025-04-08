#pragma once

#include <clang-c/Index.h>
#include <napi.h>

#include "loader.h"

template <typename T>
struct Deref
{
};

template <typename T>
struct Deref<T*>
{
    using type = T;
};

inline nc::Library* getLib(Napi::Env env)
{
    return env.GetInstanceData<nc::Library>();
}

inline void setLib(Napi::Env env, nc::Library* lib)
{
    env.SetInstanceData(lib);
}

inline Napi::External<CXCursor> wrapCursor(Napi::Env env, CXCursor cursor)
{
    return Napi::External<CXCursor>::New(env, new CXCursor(cursor), [](Napi::Env env, CXCursor* data) { delete data; });
}

inline CXCursor unwrapCursor(Napi::Value cursor)
{
    return *cursor.As<Napi::External<CXCursor>>().Data();
}
