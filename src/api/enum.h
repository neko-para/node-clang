#pragma once

#include <map>

#include <clang-c/Index.h>
#include <napi.h>

extern std::map<CXCursorKind, std::string> cursorKind_enum2str;
extern std::map<std::string, CXCursorKind> cursorKind_str2enum;
extern std::map<CXTypeKind, std::string> typeKind_enum2str;
extern std::map<std::string, CXTypeKind> typeKind_str2enum;

void implEnum(Napi::Object exports);
