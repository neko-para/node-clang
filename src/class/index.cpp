#include "index.h"

#include "../loader/clang.h"
#include "instance.h"
#include "clang-c/Index.h"
#include <cstdint>
#include <iostream>
#include <memory>

#define BIND_GETTER_SETTER(name)                                                 \
    InstanceAccessor(                                                            \
        #name,                                                                   \
        &IndexOptions::dispatcher<"get " #name, &IndexOptions::get##name>,       \
        &IndexOptions::dispatcherSetter<"set " #name, &IndexOptions::set##name>, \
        napi_enumerable)

Napi::Function IndexOptions::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CIndexOptions",
        {
            BIND_GETTER_SETTER(Size),
            BIND_GETTER_SETTER(ThreadBackgroundPriorityForIndexing),
            BIND_GETTER_SETTER(ThreadBackgroundPriorityForEditing),
            BIND_GETTER_SETTER(ExcludeDeclarationsFromPCH),
            BIND_GETTER_SETTER(DisplayDiagnostics),
            BIND_GETTER_SETTER(StorePreamblesInMemory),
            BIND_GETTER_SETTER(PreambleStoragePath),
            BIND_GETTER_SETTER(InvocationEmissionPath),
        });
    Instance::get(env).indexOptionsConstructor = Napi::Persistent(func);
    return func;
}

unsigned IndexOptions::getSize()
{
    return data.Size;
}

void IndexOptions::setSize(unsigned value)
{
    data.Size = value;
}

bool IndexOptions::getThreadBackgroundPriorityForIndexing()
{
    return data.ThreadBackgroundPriorityForIndexing;
}

void IndexOptions::setThreadBackgroundPriorityForIndexing(bool value)
{
    data.ThreadBackgroundPriorityForIndexing = value ? CXGlobalOpt_ThreadBackgroundPriorityForIndexing : 0;
}

bool IndexOptions::getThreadBackgroundPriorityForEditing()
{
    return data.ThreadBackgroundPriorityForEditing;
}

void IndexOptions::setThreadBackgroundPriorityForEditing(bool value)
{
    data.ThreadBackgroundPriorityForEditing = value ? CXGlobalOpt_ThreadBackgroundPriorityForEditing : 0;
}

bool IndexOptions::getExcludeDeclarationsFromPCH()
{
    return data.ExcludeDeclarationsFromPCH;
}

void IndexOptions::setExcludeDeclarationsFromPCH(bool value)
{
    data.ExcludeDeclarationsFromPCH = value ? 1 : 0;
}

bool IndexOptions::getDisplayDiagnostics()
{
    return data.DisplayDiagnostics;
}

void IndexOptions::setDisplayDiagnostics(bool value)
{
    data.DisplayDiagnostics = value ? 1 : 0;
}

bool IndexOptions::getStorePreamblesInMemory()
{
    return data.StorePreamblesInMemory;
}

void IndexOptions::setStorePreamblesInMemory(bool value)
{
    data.StorePreamblesInMemory = value ? 1 : 0;
}

std::optional<std::string> IndexOptions::getPreambleStoragePath()
{
    return __PreambleStoragePath;
}

void IndexOptions::setPreambleStoragePath(std::optional<std::string> value)
{
    __PreambleStoragePath = value;
    data.PreambleStoragePath = __PreambleStoragePath ? __PreambleStoragePath.value().c_str() : nullptr;
}

std::optional<std::string> IndexOptions::getInvocationEmissionPath()
{
    return __InvocationEmissionPath;
}

void IndexOptions::setInvocationEmissionPath(std::optional<std::string> value)
{
    __InvocationEmissionPath = value;
    data.InvocationEmissionPath = __InvocationEmissionPath ? __InvocationEmissionPath.value().c_str() : nullptr;
}

Napi::Function Index::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CIndex",
        {
            InstanceMethod("create", &Index::dispatcher<"create", &Index::create, &Index::createIndexWithOptions>),
            InstanceAccessor("globalOptions", &Index::dispatcher<"get globalOptions", &Index::getGlobalOptions>, nullptr),

            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &Index::dispatcher<"nodejs inspect", &Index::nodejsInspect>),
        });
    Instance::get(env).indexConstructor = Napi::Persistent(func);
    return func;
}

Index::Index(const Napi::CallbackInfo& info)
    : WrapBase<Index>(info)
    , state(std::make_shared<State>(Env()))
{
}

bool Index::create(bool excludeDeclarationsFromPCH, bool displayDiagnostics)
{
    state->data = library()->createIndex(excludeDeclarationsFromPCH, displayDiagnostics);
    return !!state->data;
}

bool Index::createIndexWithOptions(ConvertRef<IndexOptions> options)
{
    state->data = library()->createIndexWithOptions(&options.data->data);
    return !!state->data;
}

unsigned Index::getGlobalOptions()
{
    return library()->CXIndex_getGlobalOptions(state->data);
}

std::string Index::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    if (state->data) {
        return std::format("CXIndex {{ {:#018x} }}", reinterpret_cast<uintptr_t>(state->data));
    }
    else {
        return "CXIndex { nullptr }";
    }
}

Index::State::~State()
{
    if (data) {
        Instance::get(env).library->disposeIndex(data);
    }
}
