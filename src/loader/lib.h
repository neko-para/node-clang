#pragma once

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using lib_t = HMODULE;

inline lib_t lib_open(const char* path)
{
    return LoadLibraryA(path);
}

inline void lib_close(lib_t lib)
{
    CloseHandle(lib);
}

template <typename prototype>
inline prototype lib_get_func(lib_t lib, const char* name)
{
    return reinterpret_cast<prototype>(GetProcAddress(lib, name));
}
#else
#include <dlfcn.h>

using lib_t = void*;

inline lib_t lib_open(const char* path)
{
    return dlopen(path, RTLD_LAZY);
}

inline void lib_close(lib_t lib)
{
    dlclose(lib);
}

template <typename prototype>
inline prototype lib_get_func(lib_t lib, const char* name)
{
    return reinterpret_cast<prototype>(dlsym(lib, name));
}
#endif
