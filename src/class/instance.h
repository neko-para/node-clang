#pragma once

#include <format>
#include <map>
#include <sstream>

#include <napi.h>

#include "class/utils.h"
#include "loader/clang.h"

#define nc_anno(desc) [[clang::annotate(desc)]]

#define nc_inspect nc_anno("inspect")
#define nc_method nc_anno("method")
#define nc_method_as(name) nc_anno("method:" #name)
#define nc_getter nc_anno("getter")
#define nc_getter_as(name) nc_anno("getter:" #name)
#define nc_setter nc_anno("setter")
#define nc_setter_as(name) nc_anno("setter:" #name)

struct IndexOptions;
struct Index;
struct TranslationUnit;
struct Cursor;
struct CursorSet;
struct Type;
struct File;
struct Global;
struct VirtualFileOverlay;
struct ModuleMapDescriptor;
struct SourceLocation;
struct SourceRange;
struct Diagnostic;
struct DiagnosticSet;

struct Instance
{
    Library* library {};
    Napi::FunctionReference indexOptionsConstructor;
    Napi::FunctionReference indexConstructor;
    Napi::FunctionReference translationUnitConstructor;
    Napi::FunctionReference cursorConstructor;
    Napi::FunctionReference cursorSetConstructor;
    Napi::FunctionReference typeConstructor;
    Napi::FunctionReference fileConstructor;
    Napi::FunctionReference globalConstructor;
    Napi::FunctionReference virtualFileOverlayConstructor;
    Napi::FunctionReference moduleMapDescriptorConstructor;
    Napi::FunctionReference sourceLocationConstructor;
    Napi::FunctionReference sourceRangeConstructor;
    Napi::FunctionReference diagnosticConstructor;
    Napi::FunctionReference diagnosticSetConstructor;

    std::map<CXTranslationUnit, Napi::ObjectReference> translationUnits;

    static void init(Napi::Env env) { env.SetInstanceData<Instance>(new Instance); }

    static Instance& get(Napi::Env env) { return *env.GetInstanceData<Instance>(); }
};

template <auto N>
struct StringLitteral
{
    constexpr StringLitteral(const char (&str)[N]) { std::copy_n(str, N, value); }

    char value[N];
};

template <typename Type>
struct WrapBase : Napi::ObjectWrap<Type>
{
    using Napi::ObjectWrap<Type>::ObjectWrap;

    auto& instance() { return Instance::get(Napi::ObjectWrap<Type>::Env()); }

    auto library() { return instance().library; }

    template <StringLitteral name, auto... impl>
    Napi::Value dispatcher(const Napi::CallbackInfo& info)
    {
        constexpr auto func = wrap<Type, impl...>();
        std::vector<std::string> trace;
        auto result = func(static_cast<Type&>(*this), info, trace);
        if (result.has_value()) {
            return result.value();
        }
        else {
            std::ostringstream traceResult;
            for (const auto& err : trace) {
                traceResult << err << '\n';
            }
            Napi::Error::New(info.Env(), std::format("nodeClang: cannot resolve {}\n{}", name.value, traceResult.str()))
                .ThrowAsJavaScriptException();
            return info.Env().Null();
        }
    }

    template <StringLitteral name, auto... impl>
    static Napi::Value dispatcherStatic(const Napi::CallbackInfo& info)
    {
        constexpr auto func = wrapStatic<impl...>();
        std::vector<std::string> trace;
        auto result = func(info, trace);
        if (result.has_value()) {
            return result.value();
        }
        else {
            std::ostringstream traceResult;
            for (const auto& err : trace) {
                traceResult << err << '\n';
            }
            Napi::Error::New(info.Env(), std::format("nodeClang: cannot resolve {}\n{}", name.value, traceResult.str()))
                .ThrowAsJavaScriptException();
            return info.Env().Null();
        }
    }

    template <StringLitteral name, auto... impl>
    void dispatcherSetter(const Napi::CallbackInfo& info, const Napi::Value& value)
    {
        constexpr auto func = wrapSetter<Type, impl...>();
        std::vector<std::string> trace;
        auto result = func(static_cast<Type&>(*this), info, value, trace);
        if (result.has_value()) {
            return;
        }
        else {
            std::ostringstream traceResult;
            for (const auto& err : trace) {
                traceResult << err << '\n';
            }
            Napi::Error::New(info.Env(), std::format("nodeClang: cannot resolve {}\n{}", name.value, traceResult.str()))
                .ThrowAsJavaScriptException();
            return;
        }
    }

    std::string getStr(CXString str, bool dispose = true)
    {
        std::string res = library()->getCString(str);
        if (dispose) {
            library()->disposeString(str);
        }
        return res;
    }

    static std::string getStr(Napi::Env env, CXString str, bool dispose = true)
    {
        std::string res = Instance::get(env).library->getCString(str);
        if (dispose) {
            Instance::get(env).library->disposeString(str);
        }
        return res;
    }
};
