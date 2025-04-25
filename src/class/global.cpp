#include "class/global.h"

unsigned long long Global::buildSessionTimestamp(Napi::Env env)
{
    return Instance::get(env).library->getBuildSessionTimestamp();
}
