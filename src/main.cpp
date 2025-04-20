#include <clang-c/Index.h>
#include <napi.h>

#include "class/classes.h"
#include "enum.h"
#include "loader/clang.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Instance::init(env);

    exports["load"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto& inst = Instance::get(info.Env());
            if (inst.library) {
                delete inst.library;
                inst.library = nullptr;
            }

            auto result = Napi::Object::New(info.Env());

            try {
                auto library = new Library(info[0].As<Napi::String>().Utf8Value().c_str());
                inst.library = library;
            }
            catch (const char* err) {
                Napi::Error::New(info.Env(), err).ThrowAsJavaScriptException();
                return Napi::Boolean::New(info.Env(), false);
            }

            return Napi::Boolean::New(info.Env(), true);
        },
        "nodeClang.load");

    exports["loaded"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value { return Napi::Boolean::New(info.Env(), !!Instance::get(info.Env()).library); },
        "nodeClang.loaded");

    implEnum(exports);

    exports["CIndex"] = Index::Init(env);
    exports["CIndexOptions"] = IndexOptions::Init(env);
    exports["CTranslationUnit"] = TranslationUnit::Init(env);
    exports["CCursor"] = Cursor::Init(env);
    exports["CType"] = Type::Init(env);
    exports["CFile"] = File::Init(env);
    exports["CSourceLocation"] = SourceLocation::Init(env);

    /*
    exports["parseTranslationUnit"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            std::vector<std::string> command_line_args_data;
            std::vector<const char*> command_line_args;
            auto command_line_args_arr = info[2].As<Napi::Array>();
            for (uint32_t i = 0; i < command_line_args_arr.Length(); i++) {
                command_line_args_data.push_back(toStr(command_line_args_arr[i]));
                command_line_args.push_back(command_line_args_data.back().c_str());
            }

            // TODO: unsave file

            auto tu = getLib(info.Env())
                          ->call_clang_func(
                              clang_parseTranslationUnit,
                              unwrapPtr<CXIndex>(info[0]),
                              toStr(info[1]).c_str(),
                              command_line_args.empty() ? nullptr : command_line_args.data(),
                              command_line_args.size(),
                              nullptr,
                              0,
                              toU32(info[4]));
            if (!tu) {
                return info.Env().Null();
            }
            else {
                return wrapTu(info.Env(), tu);
            }
        },
        "nodeClang.parseTranslationUnit");

    exports["getTranslationUnitCursor"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto cursor = getLib(info.Env())->call_clang_func(clang_getTranslationUnitCursor, unwrapPtr<CXTranslationUnit>(info[0]));

            return wrap(info.Env(), cursor);
        },
        "nodeClang.getTranslationUnitCursor");

    exports["visitChildren"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            struct VisitChildrenContext
            {
                Napi::Env env;
                Napi::Function func;
            } ctx = {
                info.Env(),
                info[1].As<Napi::Function>(),
            };
            auto result = getLib(info.Env())
                              ->call_clang_func(
                                  clang_visitChildren,
                                  unwrap<CXCursor>(info[0]),
                                  [](CXCursor cursor, CXCursor parent, CXClientData client_data) -> CXChildVisitResult {
                                      VisitChildrenContext* ctx = reinterpret_cast<VisitChildrenContext*>(client_data);
                                      auto result = ctx->func.Call(
                                          {
                                              wrap(ctx->env, cursor),
                                              wrap(ctx->env, parent),
                                          });
                                      auto action = toI32(result);
                                      return static_cast<CXChildVisitResult>(action);
                                  },
                                  &ctx);
            return Napi::Boolean::New(info.Env(), !!result);
        },
        "nodeClang.visitChildren");
*/

    return exports;
}

NODE_API_MODULE(nodeClang, Init);
