#include "loader.h"
#include <napi.h>

#include <clang-c/Index.h>

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  nc::Library lib("");
  CXString str;
  lib.call_clang_func(clang_disposeString, str);
  return exports;
}

NODE_API_MODULE(nodeClang, Init);
