#pragma once

#include <clang-c/Index.h>
#include <cstdint>
#include <napi.h>

#include "loader.h"
#include "clang-c/CXDiagnostic.h"

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
inline Napi::External<typename Deref<Type>::type> wrapPtr(Napi::Env env, Type val)
{
    return Napi::External<typename Deref<Type>::type>::New(env, val);
}

inline Napi::External<Deref<CXIndex>::type> wrapIndex(Napi::Env env, CXIndex index)
{
    return Napi::External<Deref<CXIndex>::type>::New(env, index, [](Napi::Env env, CXIndex data) {
        getLib(env)->call_clang_func(clang_disposeIndex, data);
    });
}

inline Napi::External<Deref<CXTranslationUnit>::type> wrapTu(Napi::Env env, CXTranslationUnit tu)
{
    return Napi::External<Deref<CXTranslationUnit>::type>::New(env, tu, [](Napi::Env env, CXTranslationUnit data) {
        getLib(env)->call_clang_func(clang_disposeTranslationUnit, data);
    });
}

inline Napi::External<Deref<CXDiagnostic>::type> wrapDiag(Napi::Env env, CXDiagnostic diag)
{
    return Napi::External<Deref<CXDiagnostic>::type>::New(env, diag, [](Napi::Env env, CXDiagnostic data) {
        getLib(env)->call_clang_func(clang_disposeDiagnostic, data);
    });
}

inline Napi::External<Deref<CXDiagnosticSet>::type> wrapDiagSet(Napi::Env env, CXDiagnosticSet diags)
{
    return Napi::External<Deref<CXDiagnosticSet>::type>::New(env, diags, [](Napi::Env env, CXDiagnosticSet data) {
        getLib(env)->call_clang_func(clang_disposeDiagnosticSet, data);
    });
}

template <typename Type>
inline Type unwrap(Napi::Value val)
{
    return *val.As<Napi::External<Type>>().Data();
}

template <typename Type>
inline Type unwrapPtr(Napi::Value val)
{
    return val.As<Napi::External<typename Deref<Type>::type>>().Data();
}

inline std::string toStr(Napi::Value val)
{
    return val.As<Napi::String>().Utf8Value();
}

inline bool toBool(Napi::Value val)
{
    return val.As<Napi::Boolean>().Value();
}

inline Napi::Number toNum(Napi::Value val)
{
    return val.As<Napi::Number>();
}

inline unsigned toU32(Napi::Value val)
{
    return toNum(val).Uint32Value();
}

inline int toI32(Napi::Value val)
{
    return toNum(val).Int32Value();
}

inline uint8_t toU8(Napi::Value val)
{
    return toNum(val).Uint32Value();
}
