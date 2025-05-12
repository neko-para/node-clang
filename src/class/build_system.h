#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"
#include "class/types.h"

struct [[clang::annotate("class")]] VirtualFileOverlay : public WrapBase<VirtualFileOverlay>
{
    static Napi::Function Init(Napi::Env env);

    VirtualFileOverlay(const Napi::CallbackInfo& info);

    nc_method static std::optional<ConvertReturn<VirtualFileOverlay>> create(Napi::Env env);
    nc_method int addFileMapping(std::string virtualPath, std::string realPath);
    nc_setter void setCaseSensitivity(bool caseSensitive);
    nc_method Either<Napi::ArrayBuffer, int> writeToBuffer();

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

    nc_method static std::optional<ConvertReturn<ModuleMapDescriptor>> create(Napi::Env env);
    nc_setter void setFrameworkModuleName(std::string name);
    nc_setter void setUmbrellaHeader(std::string name);
    nc_method Either<Napi::ArrayBuffer, int> writeToBuffer();

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

