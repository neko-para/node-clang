#include "class/build_system.h"

#include <cstring>

#include "class/instance.h"
#include "class/utils.h"

VirtualFileOverlay::VirtualFileOverlay(const Napi::CallbackInfo& info)
    : WrapBase<VirtualFileOverlay>(info)
    , state(std::make_shared<State>(Env()))
{
}

bool VirtualFileOverlay::create()
{
    state->data = library()->VirtualFileOverlay_create(0);
    return !!state->data;
}

int VirtualFileOverlay::addFileMapping(std::string virtualPath, std::string realPath)
{
    return library()->VirtualFileOverlay_addFileMapping(state->data, virtualPath.c_str(), realPath.c_str());
}

void VirtualFileOverlay::setCaseSensitivity(bool caseSensitive)
{
    auto err = library()->VirtualFileOverlay_setCaseSensitivity(state->data, caseSensitive);
    throwErrorCode(Env(), err);
}

Napi::ArrayBuffer VirtualFileOverlay::writeToBuffer()
{
    char* buffer;
    unsigned size;
    auto err = library()->VirtualFileOverlay_writeToBuffer(state->data, 0, &buffer, &size);
    if (throwErrorCode(Env(), err)) {
        return Napi::ArrayBuffer::New(Env(), 0);
    }
    auto res = Napi::ArrayBuffer::New(Env(), size);
    std::memcpy(res.Data(), buffer, size);
    library()->free(buffer);
    return res;
}

VirtualFileOverlay::State::~State()
{
    if (data) {
        Instance::get(env).library->VirtualFileOverlay_dispose(data);
    }
}

ModuleMapDescriptor::ModuleMapDescriptor(const Napi::CallbackInfo& info)
    : WrapBase<ModuleMapDescriptor>(info)
    , state(std::make_shared<State>(Env()))
{
}

bool ModuleMapDescriptor::create()
{
    state->data = library()->ModuleMapDescriptor_create(0);
    return !!state->data;
}

void ModuleMapDescriptor::setFrameworkModuleName(std::string name)
{
    auto err = library()->ModuleMapDescriptor_setFrameworkModuleName(state->data, name.c_str());
    throwErrorCode(Env(), err);
}

void ModuleMapDescriptor::setUmbrellaHeader(std::string name)
{
    auto err = library()->ModuleMapDescriptor_setUmbrellaHeader(state->data, name.c_str());
    throwErrorCode(Env(), err);
}

Napi::ArrayBuffer ModuleMapDescriptor::writeToBuffer()
{
    char* buffer;
    unsigned size;
    auto err = library()->ModuleMapDescriptor_writeToBuffer(state->data, 0, &buffer, &size);
    if (throwErrorCode(Env(), err)) {
        return Napi::ArrayBuffer::New(Env(), 0);
    }
    auto res = Napi::ArrayBuffer::New(Env(), size);
    std::memcpy(res.Data(), buffer, size);
    library()->free(buffer);
    return res;
}

ModuleMapDescriptor::State::~State()
{
    if (data) {
        Instance::get(env).library->ModuleMapDescriptor_dispose(data);
    }
}
