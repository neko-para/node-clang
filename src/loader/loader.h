#pragma once

#include "loader/lib.h"

struct LibraryBase
{
    LibraryBase(const char* path)
    {
        library_ = lib_open(path);
        if (!library_) {
            throw "nodeClang: load library failed";
        }
    }

    ~LibraryBase()
    {
        if (library_) {
            lib_close(library_);
        }
    }

    lib_t library_;
};
