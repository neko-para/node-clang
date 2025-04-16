#pragma once

#include <exception>
#include <format>
#include <string>

#include <clang-c/Index.h>
#include <napi.h>

struct ConvertFailed : public std::exception
{
    std::string error;

    ConvertFailed(std::string err)
        : error(err)
    {
    }

    virtual const char* what() const noexcept override { return error.c_str(); }
};

struct ConvertAny
{
};

template <typename Type>
struct ConvertRef
{
    Type* data;
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

template <typename Type>
struct Convert
{
    static Napi::Value to_value(Napi::Env env, Type value) = delete;
    static Type from_value(Napi::Value value) = delete;
};

template <>
struct Convert<ConvertAny>
{
    static std::string name() { return "any"; }

    static Napi::Value to_value(Napi::Env env, ConvertAny value) { return env.Null(); };

    template <size_t I>
    static ConvertAny from_value(Napi::Value value)
    {
        return {};
    };
};

template <>
struct Convert<bool>
{
    static std::string name() { return "boolean"; }

    static Napi::Value to_value(Napi::Env env, bool value) { return Napi::Boolean::New(env, value); }

    template <size_t I>
    static bool from_value(Napi::Value value)
    {
        if (!value.IsBoolean()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        return value.As<Napi::Boolean>().Value();
    }
};

template <>
struct Convert<int>
{
    static std::string name() { return "number(i32)"; }

    static Napi::Value to_value(Napi::Env env, int value) { return Napi::Number::New(env, value); }

    template <size_t I>
    static int from_value(Napi::Value value)
    {
        if (!value.IsNumber()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        return value.As<Napi::Number>().Int32Value();
    }
};

template <>
struct Convert<unsigned>
{
    static std::string name() { return "number(u32)"; }

    static Napi::Value to_value(Napi::Env env, unsigned value) { return Napi::Number::New(env, value); }

    template <size_t I>
    static unsigned from_value(Napi::Value value)
    {
        if (!value.IsNumber()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        return value.As<Napi::Number>().Uint32Value();
    }
};

template <>
struct Convert<std::string>
{
    static std::string name() { return "string"; }

    static Napi::Value to_value(Napi::Env env, std::string value) { return Napi::String::New(env, value); }

    template <size_t I>
    static std::string from_value(Napi::Value value)
    {
        if (!value.IsString()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        return value.As<Napi::String>().Utf8Value();
    }
};

template <typename Type>
struct Convert<std::optional<Type>>
{
    static std::string name() { return std::format("{} | null", Convert<Type>::name()); }

    static Napi::Value to_value(Napi::Env env, std::optional<Type> value)
    {
        if (value.has_value()) {
            return Convert<Type>::to_value(env, value.value());
        }
        else {
            return env.Null();
        }
    }

    template <size_t I>
    static std::optional<Type> from_value(Napi::Value value)
    {
        if (value.IsNull()) {
            return std::nullopt;
        }
        else {
            return Convert<Type>::template from_value<I>(value);
        }
    }
};

template <typename Type>
struct Convert<ConvertRef<Type>>
{
    static std::string name() { return std::format("object({})", typeid(Type).name()); }

    static Napi::Value to_value(Napi::Env env, ConvertRef<Type> value) { return env.Null(); }

    template <size_t I>
    static ConvertRef<Type> from_value(Napi::Value value)
    {
        if (!value.IsObject()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        try {
            return { Type::Unwrap(value.As<Napi::Object>()) };
        }
        catch (const Napi::Error& error) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
    }
};
