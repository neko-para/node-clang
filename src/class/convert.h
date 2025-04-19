#pragma once

#include <array>
#include <exception>
#include <format>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <variant>

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

struct ConvertNull
{
};

template <typename Type>
struct ConvertRef
{
    Type* data;
};

template <typename Type>
struct ConvertReturn
{
    Napi::Value data;
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
struct Convert<long>
{
    static std::string name() { return "number(i64)"; }

    static Napi::Value to_value(Napi::Env env, long value)
    {
        if (value > ((1ll << 53) - 1) || value < -((1ll << 53) - 1)) {
            return Napi::BigInt::New(env, static_cast<int64_t>(value));
        }
        else {
            return Napi::Number::New(env, value);
        }
    }

    template <size_t I>
    static long from_value(Napi::Value value)
    {
        if (!value.IsNumber() && !value.IsBigInt()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        if (value.IsNumber()) {
            return value.As<Napi::Number>().Int64Value();
        }
        else {
            bool suc;
            return value.As<Napi::BigInt>().Int64Value(&suc);
        }
    }
};

template <>
struct Convert<unsigned long>
{
    static std::string name() { return "number(u64)"; }

    static Napi::Value to_value(Napi::Env env, unsigned long value)
    {
        if (value > ((1ull << 53) - 1)) {
            return Napi::BigInt::New(env, static_cast<uint64_t>(value));
        }
        else {
            return Napi::Number::New(env, value);
        }
    }

    template <size_t I>
    static unsigned long from_value(Napi::Value value)
    {
        if (!value.IsNumber() && !value.IsBigInt()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        if (value.IsNumber()) {
            return value.As<Napi::Number>().Int64Value();
        }
        else {
            bool suc;
            return value.As<Napi::BigInt>().Uint64Value(&suc);
        }
    }
};

template <>
struct Convert<long long>
{
    static std::string name() { return "number(i64)"; }

    static Napi::Value to_value(Napi::Env env, long long value)
    {
        if (value > ((1ll << 53) - 1) || value < -((1ll << 53) - 1)) {
            return Napi::BigInt::New(env, static_cast<int64_t>(value));
        }
        else {
            return Napi::Number::New(env, value);
        }
    }

    template <size_t I>
    static long long from_value(Napi::Value value)
    {
        if (!value.IsNumber() && !value.IsBigInt()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        if (value.IsNumber()) {
            return value.As<Napi::Number>().Int64Value();
        }
        else {
            bool suc;
            return value.As<Napi::BigInt>().Int64Value(&suc);
        }
    }
};

template <>
struct Convert<unsigned long long>
{
    static std::string name() { return "number(u64)"; }

    static Napi::Value to_value(Napi::Env env, unsigned long long value)
    {
        if (value > ((1ull << 53) - 1)) {
            return Napi::BigInt::New(env, static_cast<uint64_t>(value));
        }
        else {
            return Napi::Number::New(env, value);
        }
    }

    template <size_t I>
    static unsigned long long from_value(Napi::Value value)
    {
        if (!value.IsNumber() && !value.IsBigInt()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        if (value.IsNumber()) {
            return value.As<Napi::Number>().Int64Value();
        }
        else {
            bool suc;
            return value.As<Napi::BigInt>().Uint64Value(&suc);
        }
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
struct Convert<std::vector<Type>>
{
    static std::string name() { return std::format("({})[]", Convert<Type>::name()); }

    static Napi::Value to_value(Napi::Env env, std::vector<Type> value)
    {
        auto result = Napi::Array ::New(env, value.size());
        for (uint32_t i = 0; i < value.size(); i++) {
            result[i] = Convert<Type>::to_value(env, value[i]);
        }
        return result;
    }

    template <size_t I>
    static std::vector<Type> from_value(Napi::Value value)
    {
        if (!value.IsArray()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        auto arr = value.As<Napi::Array>();
        std::vector<Type> result(arr.Length());
        for (uint32_t i = 0; i < arr.Length(); i++) {
            result[i] = Convert<Type>::template from_value<I>(arr[i]);
        }
        return result;
    }
};

template <typename Type, size_t N>
struct Convert<std::array<Type, N>>
{
    static std::string name() { return std::format("({})[{}]", Convert<Type>::name(), N); }

    static Napi::Value to_value(Napi::Env env, std::array<Type, N> value)
    {
        auto result = Napi::Array ::New(env, N);
        for (uint32_t i = 0; i < N; i++) {
            result[i] = Convert<Type>::to_value(env, value[i]);
        }
        return result;
    }

    template <size_t I>
    static std::array<Type, N> from_value(Napi::Value value)
    {
        if (!value.IsArray()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        auto arr = value.As<Napi::Array>();
        if (arr.Length() != N) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        std::array<Type, N> result;
        for (uint32_t i = 0; i < N; i++) {
            result[i] = Convert<Type>::template from_value<I>(arr[i]);
        }
        return result;
    }
};

template <typename... Type>
struct Convert<std::tuple<Type...>>
{
    using args_t = std::tuple<Type...>;

    static std::string name()
    {
        std::string decl;
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            ((decl += Convert<std::tuple_element_t<Is, args_t>>::name(), decl += ", "), ...);
        }(std::make_index_sequence<std::tuple_size_v<args_t>>());
        if (decl.length() > 1) {
            decl.pop_back();
            decl.pop_back();
        }
        return std::format("[{}]", decl);
    }

    static Napi::Value to_value(Napi::Env env, std::tuple<Type...> value)
    {
        auto result = Napi::Array::New(env, std::tuple_size_v<args_t>);

        [&]<size_t... Is>(std::index_sequence<Is...>) {
            ((result[Is] = Convert<std::tuple_element_t<Is, args_t>>::to_value(env, std::get<Is>(value))), ...);
        }(std::make_index_sequence<std::tuple_size_v<args_t>>());

        return result;
    }

    template <size_t I>
    static std::tuple<Type...> from_value(Napi::Value value)
    {
        if (!value.IsArray()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        auto arr = value.As<Napi::Array>();
        if (arr.Length() != std::tuple_size_v<args_t>) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        std::tuple<Type...> result;
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            ((std::get<Is>(result) = Convert<std::tuple_element_t<Is, args_t>>::template from_value<I>(arr[Is])), ...);
        }(std::make_index_sequence<std::tuple_size_v<args_t>>());
        return result;
    }
};

template <typename... Type>
struct Convert<std::variant<Type...>>
{
    using args_t = std::tuple<Type...>;

    static std::string name()
    {
        std::string decl;
        [&]<size_t... Is>(std::index_sequence<Is...>) {
            ((decl += Convert<std::tuple_element_t<Is, args_t>>::name(), decl += " | "), ...);
        }(std::make_index_sequence<std::tuple_size_v<args_t>>());
        if (decl.length() > 2) {
            decl.pop_back();
            decl.pop_back();
            decl.pop_back();
        }
        return decl;
    }

    static Napi::Value to_value(Napi::Env env, std::variant<Type...> value)
    {
        Napi::Value result = env.Null();

        [&]<size_t... Is>(std::index_sequence<Is...>) {
            return (
                (value.index() == Is ? (result = Convert<std::tuple_element_t<Is, args_t>>::to_value(env, std::get<Is>(value))),
                 true
                                     : false)
                || ...);
        }(std::make_index_sequence<std::tuple_size_v<args_t>>());

        return result;
    }

    template <size_t I>
    static std::variant<Type...> from_value(Napi::Value value)
    {
        std::variant<Type...> result;
        std::vector<std::string> trace;
        bool success = [&]<size_t... Is>(std::index_sequence<Is...>) {
            return ((try_from_value<I, Is>(value, result, trace)) || ...);
        }(std::make_index_sequence<std::tuple_size_v<args_t>>());
        if (!success) {
            std::ostringstream traceResult;
            for (const auto& err : trace) {
                traceResult << err << '\n';
            }
            throw ConvertFailed {
                std::format("Type mismatch at {}, expect {}, got {}\n{}", I, name(), valueType(value), traceResult.str())
            };
        }
        return result;
    }

    template <size_t I, size_t II>
    static bool try_from_value(Napi::Value value, std::variant<Type...>& result, std::vector<std::string>& trace)
    {
        try {
            std::get<II>(result) = Convert<std::tuple_element_t<II, args_t>>::template from_value<I>(value);
            return true;
        }
        catch (ConvertFailed error) {
            trace.push_back(std::format("    Tried ({}) failed: {}", Convert<std::tuple_element_t<II, args_t>>::name(), error.error));
        }
        return false;
    }
};

template <>
struct Convert<Napi::Function>
{
    static std::string name() { return "function"; }

    static Napi::Value to_value(Napi::Env env, Napi::Function value) { return value; }

    template <size_t I>
    static Napi::Function from_value(Napi::Value value)
    {
        if (!value.IsFunction()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        return value.As<Napi::Function>();
    }
};

template <>
struct Convert<Napi::Date>
{
    static std::string name() { return "date"; }

    static Napi::Value to_value(Napi::Env env, Napi::Date value) { return value; }

    template <size_t I>
    static Napi::Date from_value(Napi::Value value)
    {
        if (!value.IsDate()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        return value.As<Napi::Date>();
    }
};

template <>
struct Convert<ConvertNull>
{
    static std::string name() { return "null"; }

    static Napi::Value to_value(Napi::Env env, ConvertNull value) { return env.Null(); }

    template <size_t I>
    static ConvertNull from_value(Napi::Value value)
    {
        if (!value.IsNull()) {
            throw ConvertFailed { std::format("Type mismatch at {}, expect {}, got {}", I, name(), valueType(value)) };
        }
        return {};
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

template <typename Type>
struct Convert<ConvertReturn<Type>>
{
    static std::string name() { return std::format("object({})", typeid(Type).name()); }

    static Napi::Value to_value(Napi::Env env, ConvertReturn<Type> value) { return value.data; }

    template <size_t I>
    static ConvertReturn<Type> from_value(Napi::Value value)
    {
        throw ConvertFailed { "" };
    }
};
