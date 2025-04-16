#pragma once

#include <clang-c/Index.h>
#include <memory>
#include <napi.h>
#include <string>

#include "convert.h"
#include "instance.h"

struct IndexOptions : public WrapBase<IndexOptions>
{
public:
    static Napi::Function Init(Napi::Env env);

    using WrapBase::WrapBase;

    unsigned getSize();
    void setSize(unsigned value);

    bool getThreadBackgroundPriorityForIndexing();
    void setThreadBackgroundPriorityForIndexing(bool value);

    bool getThreadBackgroundPriorityForEditing();
    void setThreadBackgroundPriorityForEditing(bool value);

    bool getExcludeDeclarationsFromPCH();
    void setExcludeDeclarationsFromPCH(bool value);

    bool getDisplayDiagnostics();
    void setDisplayDiagnostics(bool value);

    bool getStorePreamblesInMemory();
    void setStorePreamblesInMemory(bool value);

    std::optional<std::string> getPreambleStoragePath();
    void setPreambleStoragePath(std::optional<std::string> value);

    std::optional<std::string> getInvocationEmissionPath();
    void setInvocationEmissionPath(std::optional<std::string> value);

    CXIndexOptions data;
    std::optional<std::string> __PreambleStoragePath;
    std::optional<std::string> __InvocationEmissionPath;
};

class Index : public WrapBase<Index>
{
public:
    static Napi::Function Init(Napi::Env env);

    Index(const Napi::CallbackInfo& info);

    bool create(bool excludeDeclarationsFromPCH, bool displayDiagnostics);
    bool createIndexWithOptions(ConvertRef<IndexOptions> options);
    unsigned getGlobalOptions();
    std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

private:
    struct State
    {
        Napi::Env env;
        CXIndex data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};
};

