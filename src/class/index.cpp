#include "index.h"

#include "../loader/clang.h"
#include "instance.h"

Napi::Function Index::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CIndex",
        {
            InstanceMethod("globalOptions", &Index::dispatcher<"globalOptions", &Index::globalOptions>),
        });
    Instance::get(env).indexConstructor = Napi::Persistent(func);
    return func;
}

Index::Index(const Napi::CallbackInfo& info)
    : WrapBase<Index>(info)
{
    dispatcher<"create", &Index::create>(info);
}

Index::~Index()
{
    if (data) {
        library()->disposeIndex(data);
    }
}

void Index::create(bool excludeDeclarationsFromPCH, bool displayDiagnostics)
{
    data = library()->createIndex(excludeDeclarationsFromPCH, displayDiagnostics);
}

unsigned Index::globalOptions()
{
    return library()->CXIndex_getGlobalOptions(data);
}
