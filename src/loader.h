#pragma once

#include <utility>

#include <clang-c/Index.h>

#include "lib.h"

namespace nc {

struct Library {
  Library(const char *path) { library_ = lib_open(path); }
  ~Library() {
    if (library_) {
      lib_close(library_);
    }
  }

  template <typename Prototype, typename... Args>
  auto call_clang_func(const char *symbol, Args &&...args) {
    auto func = lib_get_func(library_, symbol);
    return reinterpret_cast<Prototype>(func)(std::forward<Args>(args)...);
  }

  lib_t library_;
};

} // namespace nc

#define call_clang_func(func, ...)                                             \
  call_clang_func<decltype(func) *>(#func, ##__VA_ARGS__)
