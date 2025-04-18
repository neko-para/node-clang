#pragma once

#include <memory>
#include <string>

#include <clang-c/Index.h>
#include <napi.h>

#include "convert.h"
#include "instance.h"

class TranslationUnit : public WrapBase<TranslationUnit>
{
public:
    static Napi::Function Init(Napi::Env env);

    TranslationUnit(const Napi::CallbackInfo& info);

    void __change(CXTranslationUnit tu)
    {
        state = std::make_shared<State>(Env());
        state->data = tu;
    }

    std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

private:
    struct State
    {
        Napi::Env env;
        CXTranslationUnit data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};
};

