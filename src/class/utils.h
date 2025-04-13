#pragma once

#include <exception>
#include <format>
#include <optional>
#include <tuple>
#include <utility>

#include <napi.h>

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

struct ConvertFailed : public std::exception
{
    std::string error;

    ConvertFailed(std::string err)
        : error(err)
    {
    }

    virtual const char* what() const noexcept override { return error.c_str(); }
};

template <typename Type>
struct Convert
{
    static Napi::Value to_value(Napi::Env env, Type value) = delete;
    static Type from_value(Napi::Value value) = delete;
};

inline std::string valueType(Napi::Value value)
{
    switch (value.Type()) {
    case napi_undefined:
        return "undefined";
    case napi_null:
        return "null";
    case napi_boolean:
        return "boolean";
    case napi_number:
        return "number";
    case napi_string:
        return "string";
    case napi_symbol:
        return "symbol";
    case napi_object:
        return "object";
    case napi_function:
        return "function";
    case napi_external:
        return "external";
    case napi_bigint:
        return "bigint";
    }
    return "unknown";
}

template <>
struct Convert<bool>
{
    static constexpr const char* name = "boolean";

    static Napi::Value to_value(Napi::Env env, bool value) { return Napi::Boolean::New(env, value); }

    template <size_t I>
    static bool from_value(Napi::Value value)
    {
        if (!value.IsBoolean()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect boolean, got {}", I, valueType(value)) };
        }
        return value.As<Napi::Boolean>().Value();
    }
};

template <>
struct Convert<unsigned>
{
    static constexpr const char* name = "unsigned";

    static Napi::Value to_value(Napi::Env env, unsigned value) { return Napi::Number::New(env, value); }

    template <size_t I>
    static unsigned from_value(Napi::Value value)
    {
        if (!value.IsNumber()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect number(unsigned), got {}", I, valueType(value)) };
        }
        return value.As<Napi::Number>().Uint32Value();
    }
};

template <>
struct Convert<std::string>
{
    static constexpr const char* name = "string";

    static Napi::Value to_value(Napi::Env env, std::string value) { return Napi::String::New(env, value); }

    template <size_t I>
    static std::string from_value(Napi::Value value)
    {
        if (!value.IsString()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect string, got {}", I, valueType(value)) };
        }
        return value.As<Napi::String>().Utf8Value();
    }
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
                ((decl += Convert<std::tuple_element_t<Is, args_t>>::name, decl += ", "), ...);
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
            return wrap<Self, rest...>()(self, info, trace);
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
                    if constexpr (traits::has_self) {
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
                ((decl += Convert<std::tuple_element_t<Is, args_t>>::name, decl += ", "), ...);
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
            return wrapStatic<rest...>()(info, trace);
        }
    };
}
