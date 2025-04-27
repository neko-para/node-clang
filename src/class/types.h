#pragma once

#include <string>
#include <tuple>

#include "class/convert.h"

using UnsavedFile = std::tuple<std::string, std::string, unsigned long>;

template <typename Result>
using EitherSuccess = std::tuple<Result, ConvertNull>;

template <typename Error>
using EitherFailed = std::tuple<ConvertNull, Error>;

template <typename Result, typename Error>
using Either = std::variant<EitherSuccess<Result>, EitherFailed<Error>>;
