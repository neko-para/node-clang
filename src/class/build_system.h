#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"

struct [[clang::annotate("class")]] VirtualFileOverlay : public WrapBase<VirtualFileOverlay>
{
    static Napi::Function Init(Napi::Env env);

    VirtualFileOverlay(const Napi::CallbackInfo& info);

    [[clang::annotate("method")]] static std::optional<ConvertReturn<VirtualFileOverlay>> create(Napi::Env env);
    [[clang::annotate("method")]] int addFileMapping(std::string virtualPath, std::string realPath);
    [[clang::annotate("setter")]] void setCaseSensitivity(bool caseSensitive);
    [[clang::annotate("method")]] Napi::ArrayBuffer writeToBuffer();

    struct State
    {
        Napi::Env env;
        CXVirtualFileOverlay data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

struct [[clang::annotate("class")]] ModuleMapDescriptor : public WrapBase<ModuleMapDescriptor>
{
    static Napi::Function Init(Napi::Env env);

    ModuleMapDescriptor(const Napi::CallbackInfo& info);

    [[clang::annotate("method")]] static std::optional<ConvertReturn<ModuleMapDescriptor>> create(Napi::Env env);
    [[clang::annotate("setter")]] void setFrameworkModuleName(std::string name);
    [[clang::annotate("setter")]] void setUmbrellaHeader(std::string name);
    [[clang::annotate("method")]] Napi::ArrayBuffer writeToBuffer();

    struct State
    {
        Napi::Env env;
        CXModuleMapDescriptor data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

