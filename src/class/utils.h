#pragma once

#include <format>
#include <optional>
#include <tuple>
#include <utility>
#include <variant>

#include <napi.h>

#include "class/convert.h"

template <typename Self, typename Func>
struct FuncTraits
{
};

template <typename Self, typename Ret, typename... Args>
struct FuncTraits<Self, Ret (*)(Args...)>
{
    using return_t = Ret;
    using args_t = std::tuple<Args...>;
    static constexpr bool has_self = false;
};

template <typename Self, typename Ret, typename... Args>
struct FuncTraits<Self, Ret (Self::*)(Args...)>
{
    using return_t = Ret;
    using args_t = std::tuple<Args...>;
    static constexpr bool has_self = true;
};

template <typename Func>
struct StaticFuncTraits
{
};

template <typename Ret, typename... Args>
struct StaticFuncTraits<Ret (*)(Args...)>
{
    using return_t = Ret;
    using args_t = std::tuple<Args...>;
    static constexpr bool has_env = false;
};

template <typename Ret, typename... Args>
struct StaticFuncTraits<Ret (*)(Napi::Env, Args...)>
{
    using return_t = Ret;
    using args_t = std::tuple<Args...>;
    static constexpr bool has_env = true;
};

template <typename Self, auto func, auto... rest>
consteval inline auto wrap()
{
    using Func = decltype(func);
    return +[](Self& self, const Napi::CallbackInfo& info, std::vector<std::string>& trace) -> std::optional<Napi::Value> {
        using traits = FuncTraits<Self, Func>;
        using args_t = traits::args_t;
        try {
            do {
                if (std::tuple_size_v<args_t> != info.Length()) {
                    throw ConvertFailed { std::format("Count mismatch, expect {}, got {}", std::tuple_size_v<args_t>, info.Length()) };
                }
                args_t args;
                [&]<size_t... Is>(std::index_sequence<Is...>) {
                    ((std::get<Is>(args) = Convert<std::tuple_element_t<Is, args_t>>::template from_value<Is>(info[Is])), ...);
                }(std::make_index_sequence<std::tuple_size_v<args_t>>());
                if constexpr (std::is_same_v<typename traits::return_t, void>) {
                    if constexpr (traits::has_self) {
                        std::apply(func, std::tuple_cat(std::make_tuple<Self&>(self), args));
                    }
                    else {
                        std::apply(func, args);
                    }
                    return info.Env().Null();
                }
                else {
                    if constexpr (traits::has_self) {
                        return Convert<typename traits::return_t>::to_value(
                            info.Env(),
                            std::apply(func, std::tuple_cat(std::make_tuple<Self&>(self), args)));
                    }
                    else {
                        return Convert<typename traits::return_t>::to_value(info.Env(), std::apply(func, args));
                    }
                }
            } while (false);
        }
        catch (ConvertFailed err) {
            std::string decl;
            [&]<size_t... Is>(std::index_sequence<Is...>) {
                ((decl += Convert<std::tuple_element_t<Is, args_t>>::name(), decl += ", "), ...);
            }(std::make_index_sequence<std::tuple_size_v<args_t>>());
            if (decl.length() > 1) {
                decl.pop_back();
                decl.pop_back();
            }

            trace.push_back(std::format("    Tried ({}) failed: {}", decl, err.what()));
        }
        if constexpr (sizeof...(rest) == 0) {
            return std::nullopt;
        }
        else {
            constexpr auto next = wrap<Self, rest...>();
            return next(self, info, trace);
        }
    };
}

template <typename Self, auto func, auto... rest>
consteval inline auto wrapSetter()
{
    using Func = decltype(func);
    return +[](Self& self,
               const Napi::CallbackInfo& info,
               const Napi::Value& value,
               std::vector<std::string>& trace) -> std::optional<std::monostate> {
        using traits = FuncTraits<Self, Func>;
        using args_t = traits::args_t;
        try {
            do {
                if (info.Length() != 1) {
                    throw ConvertFailed { std::format("Count mismatch, expect 1, got {}", info.Length()) };
                }
                args_t args;
                std::get<0>(args) = Convert<std::tuple_element_t<0, args_t>>::template from_value<0>(value);
                if constexpr (traits::has_self) {
                    std::apply(func, std::tuple_cat(std::make_tuple<Self&>(self), args));
                }
                else {
                    std::apply(func, args);
                }
                return std::monostate {};
            } while (false);
        }
        catch (ConvertFailed err) {
            trace.push_back(std::format("    Tried ({}) failed: {}", Convert<std::tuple_element_t<0, args_t>>::name(), err.what()));
        }
        if constexpr (sizeof...(rest) == 0) {
            return std::nullopt;
        }
        else {
            constexpr auto next = wrapSetter<Self, rest...>();
            return next(self, info, value, trace);
        }
    };
}

template <auto func, auto... rest>
consteval inline auto wrapStatic()
{
    using Func = decltype(func);
    return +[](const Napi::CallbackInfo& info, std::vector<std::string>& trace) -> std::optional<Napi::Value> {
        using traits = StaticFuncTraits<Func>;
        using args_t = traits::args_t;
        try {
            do {
                if (std::tuple_size_v<args_t> != info.Length()) {
                    throw ConvertFailed { std::format("Count mismatch, expect {}, got {}", std::tuple_size_v<args_t>, info.Length()) };
                }
                args_t args;
                [&]<size_t... Is>(std::index_sequence<Is...>) {
                    ((std::get<Is>(args) = Convert<std::tuple_element_t<Is, args_t>>::template from_value<Is>(info[Is])), ...);
                }(std::make_index_sequence<std::tuple_size_v<args_t>>());
                if constexpr (std::is_same_v<typename traits::return_t, void>) {
                    if constexpr (traits::has_env) {
                        std::apply(func, std::tuple_cat(std::make_tuple<Napi::Env>(info.Env()), args));
                    }
                    else {
                        std::apply(func, args);
                    }
                    return info.Env().Null();
                }
                else {
                    if constexpr (traits::has_env) {
                        return Convert<typename traits::return_t>::to_value(
                            info.Env(),
                            std::apply(func, std::tuple_cat(std::make_tuple<Napi::Env>(info.Env()), args)));
                    }
                    else {
                        return Convert<typename traits::return_t>::to_value(info.Env(), std::apply(func, args));
                    }
                }
            } while (false);
        }
        catch (ConvertFailed err) {
            std::string decl;
            [&]<size_t... Is>(std::index_sequence<Is...>) {
                ((decl += Convert<std::tuple_element_t<Is, args_t>>::name(), decl += ", "), ...);
            }(std::make_index_sequence<std::tuple_size_v<args_t>>());
            if (decl.length() > 1) {
                decl.pop_back();
                decl.pop_back();
            }

            trace.push_back(std::format("    Tried ({}) failed: {}", decl, err.what()));
        }
        if constexpr (sizeof...(rest) == 0) {
            return std::nullopt;
        }
        else {
            constexpr auto next = wrapStatic<rest...>();
            return next(info, trace);
        }
    };
}

inline void throwValue(Napi::Value value)
{
    napi_throw(value.Env(), value);
}

inline bool throwErrorCode(Napi::Env env, CXErrorCode err)
{
    if (err != CXError_Success) {
        throwValue(Napi::Number::New(env, err));
        return true;
    }
    else {
        return false;
    }
}

template <typename Type>
inline Napi::Reference<Type> tryPersist(const Napi::Reference<Type>& ref)
{
    if (ref.IsEmpty()) {
        return {};
    }
    else {
        return Napi::Persistent(ref.Value());
    }
}
