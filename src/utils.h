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

template <typename Type>
inline Napi::External<Type> wrap(Napi::Env env, Type val)
{
    return Napi::External<Type>::New(env, new Type(val), [](Napi::Env env, Type* data) { delete data; });
}

template <typename Type>
inline Type unwrap(Napi::Value val)
{
    return *val.As<Napi::External<Type>>().Data();
}
