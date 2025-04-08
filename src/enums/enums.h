#pragma once

#include <map>
#include <string>
#include <tuple>

#include <napi.h>

#define ENUM_ADD(name) result[#name] = CXCursor_##name;

std::tuple<Napi::Object, Napi::Object> processEnum(Napi::Env env, std::map<std::string, int> enums);

std::map<std::string, int> makeCXCursorKindEnum();
