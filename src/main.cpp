#include <cstdint>

#include <clang-c/Index.h>
#include <napi.h>

#include "enums/enums.h"
#include "loader.h"

template <typename T>
struct Deref
{
};

template <typename T>
struct Deref<T*>
{
    using type = T;
};

nc::Library* getLib(Napi::Env env)
{
    return env.GetInstanceData<nc::Library>();
}

void setLib(Napi::Env env, nc::Library* lib)
{
    env.SetInstanceData(lib);
}

Napi::External<CXCursor> wrapCursor(Napi::Env env, CXCursor cursor)
{
    return Napi::External<CXCursor>::New(env, new CXCursor(cursor), [](Napi::Env env, CXCursor* data) { delete data; });
}

CXCursor unwrapCursor(Napi::Value cursor)
{
    return *cursor.As<Napi::External<CXCursor>>().Data();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["load"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            if (getLib(info.Env())) {
                delete getLib(info.Env());
                setLib(info.Env(), nullptr);
            }

            auto result = Napi::Object::New(info.Env());

            try {
                auto library = new nc::Library(info[0].As<Napi::String>().Utf8Value().c_str());
                setLib(info.Env(), library);
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
        [](const Napi::CallbackInfo& info) -> Napi::Value { return Napi::Boolean::New(info.Env(), !!getLib(info.Env())); },
        "nodeClang.loaded");

    exports["createIndex"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto index = getLib(info.Env())
                             ->call_clang_func(clang_createIndex, info[0].As<Napi::Boolean>().Value(), info[1].As<Napi::Boolean>().Value());
            if (!index) {
                return info.Env().Null();
            }
            else {
                return Napi::External<Deref<CXIndex>::type>::New(info.Env(), index, [](Napi::Env env, CXIndex data) {
                    getLib(env)->call_clang_func(clang_disposeIndex, data);
                });
            }
        },
        "nodeClang.createIndex");

    exports["parseTranslationUnit"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            std::vector<std::string> command_line_args_data;
            std::vector<const char*> command_line_args;
            auto command_line_args_arr = info[2].As<Napi::Array>();
            for (uint32_t i = 0; i < command_line_args_arr.Length(); i++) {
                command_line_args_data.push_back(Napi::Value(command_line_args_arr[i]).As<Napi::String>().Utf8Value());
                command_line_args.push_back(command_line_args_data.back().c_str());
            }

            auto tu = getLib(info.Env())
                          ->call_clang_func(
                              clang_parseTranslationUnit,
                              info[0].As<Napi::External<Deref<CXIndex>::type>>().Data(),
                              info[1].As<Napi::String>().Utf8Value().c_str(),
                              command_line_args.empty() ? nullptr : command_line_args.data(),
                              command_line_args.size(),
                              nullptr,
                              0,
                              info[4].As<Napi::Number>().Uint32Value());
            if (!tu) {
                return info.Env().Null();
            }
            else {
                return Napi::External<Deref<CXTranslationUnit>::type>::New(info.Env(), tu, [](Napi::Env env, CXTranslationUnit data) {
                    getLib(env)->call_clang_func(clang_disposeTranslationUnit, data);
                });
            }
        },
        "nodeClang.parseTranslationUnit");

    exports["getTranslationUnitCursor"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto cursor =
                getLib(info.Env())
                    ->call_clang_func(clang_getTranslationUnitCursor, info[0].As<Napi::External<Deref<CXTranslationUnit>::type>>().Data());

            return wrapCursor(info.Env(), cursor);
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
                                  unwrapCursor(info[0]),
                                  [](CXCursor cursor, CXCursor parent, CXClientData client_data) -> CXChildVisitResult {
                                      VisitChildrenContext* ctx = reinterpret_cast<VisitChildrenContext*>(client_data);
                                      auto result = ctx->func.Call(
                                          {
                                              wrapCursor(ctx->env, cursor),
                                              wrapCursor(ctx->env, parent),
                                          });
                                      auto action = result.As<Napi::String>().Utf8Value();
                                      if (action == "break") {
                                          return CXChildVisit_Break;
                                      }
                                      else if (action == "continue") {
                                          return CXChildVisit_Continue;
                                      }
                                      else if (action == "recurse") {
                                          return CXChildVisit_Recurse;
                                      }
                                      else {
                                          return CXChildVisit_Break;
                                      }
                                  },
                                  &ctx);
            return Napi::Boolean::New(info.Env(), !!result);
        },
        "nodeClang.visitChildren");

    exports["equalCursors"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_equalCursors, unwrapCursor(info[0]), unwrapCursor(info[1]));
            return Napi::Boolean::New(info.Env(), !!result);
        },
        "nodeClang.equalCursors");

    exports["getCursorSpelling"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getCursorSpelling, unwrapCursor(info[0]));
            auto ret = Napi::String::New(info.Env(), getLib(info.Env())->call_clang_func(clang_getCString, result));
            getLib(info.Env())->call_clang_func(clang_disposeString, result);
            return ret;
        },
        "nodeClang.getCursorSpelling");

    exports["getCursorKind"] = Napi::Function::New(
        env,
        [](const Napi::CallbackInfo& info) -> Napi::Value {
            auto result = getLib(info.Env())->call_clang_func(clang_getCursorKind, unwrapCursor(info[0]));
            return Napi::Number::New(info.Env(), result);
        },
        "nodeClang.getCursorKind");

    auto [CXCursorKind_str_to_num, CXCursorKind_num_to_str] = processEnum(env, makeCXCursorKindEnum());
    exports["__CXCursorKind_StrNum"] = CXCursorKind_str_to_num;
    exports["__CXCursorKind_NumStr"] = CXCursorKind_num_to_str;

    return exports;
}

NODE_API_MODULE(nodeClang, Init);
