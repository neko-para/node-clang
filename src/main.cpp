#include "loader.h"
#include <cstdint>
#include <napi.h>

#include <clang-c/Index.h>

template <typename T> struct Deref {};

template <typename T> struct Deref<T *> {
  using type = T;
};

nc::Library *getLib(Napi::Env env) {
  return env.GetInstanceData<nc::Library>();
}

void setLib(Napi::Env env, nc::Library *lib) { env.SetInstanceData(lib); }

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports["load"] = Napi::Function::New(
      env,
      [](const Napi::CallbackInfo &info) -> Napi::Value {
        if (getLib(info.Env())) {
          delete getLib(info.Env());
          setLib(info.Env(), nullptr);
        }

        auto result = Napi::Object::New(info.Env());

        try {
          auto library =
              new nc::Library(info[0].As<Napi::String>().Utf8Value().c_str());
          setLib(info.Env(), library);
        } catch (const char *err) {
          Napi::Error::New(info.Env(), err).ThrowAsJavaScriptException();
          return Napi::Boolean::New(info.Env(), false);
        }

        return Napi::Boolean::New(info.Env(), true);
      },
      "nodeClang.load");

  exports["loaded"] = Napi::Function::New(
      env,
      [](const Napi::CallbackInfo &info) -> Napi::Value {
        return Napi::Boolean::New(info.Env(), !!getLib(info.Env()));
      },
      "nodeClang.loaded");

  exports["createIndex"] = Napi::Function::New(
      env,
      [](const Napi::CallbackInfo &info) -> Napi::Value {
        auto index =
            getLib(info.Env())
                ->call_clang_func(clang_createIndex,
                                  info[0].As<Napi::Number>().Int32Value(),
                                  info[1].As<Napi::Number>().Int32Value());
        if (!index) {
          return info.Env().Null();
        } else {
          return Napi::External<Deref<CXIndex>::type>::New(
              info.Env(), index, [](Napi::Env env, CXIndex data) {
                getLib(env)->call_clang_func(clang_disposeIndex, data);
              });
        }
      },
      "nodeClang.createIndex");

  exports["parseTranslationUnit"] = Napi::Function::New(
      env,
      [](const Napi::CallbackInfo &info) -> Napi::Value {
        std::vector<std::string> command_line_args_data;
        std::vector<const char *> command_line_args;
        auto command_line_args_arr = info[2].As<Napi::Array>();
        for (uint32_t i = 0; i < command_line_args_arr.Length(); i++) {
          command_line_args_data.push_back(Napi::Value(command_line_args_arr[i])
                                               .As<Napi::String>()
                                               .Utf8Value());
          command_line_args.push_back(command_line_args_data.back().c_str());
        }

        auto tu =
            getLib(info.Env())
                ->call_clang_func(
                    clang_parseTranslationUnit,
                    info[0].As<Napi::External<Deref<CXIndex>::type>>().Data(),
                    info[1].As<Napi::String>().Utf8Value().c_str(),
                    command_line_args.empty() ? nullptr
                                              : command_line_args.data(),
                    command_line_args.size(), nullptr, 0,
                    info[4].As<Napi::Number>().Uint32Value());
        if (!tu) {
          return info.Env().Null();
        } else {
          return Napi::External<Deref<CXTranslationUnit>::type>::New(
              info.Env(), tu, [](Napi::Env env, CXTranslationUnit data) {
                getLib(env)->call_clang_func(clang_disposeTranslationUnit,
                                             data);
              });
        }
      },
      "nodeClang.parseTranslationUnit");

  exports["getTranslationUnitCursor"] = Napi::Function::New(
      env,
      [](const Napi::CallbackInfo &info) -> Napi::Value {
        auto cursor =
            getLib(info.Env())
                ->call_clang_func(
                    clang_getTranslationUnitCursor,
                    info[0]
                        .As<Napi::External<Deref<CXTranslationUnit>::type>>()
                        .Data());

        auto result = Napi::Object::New(info.Env());
        result["kind"] = (int)cursor.kind;
        result["__data"] = Napi::External<CXCursor>::New(
            info.Env(), new CXCursor(cursor),
            [](Napi::Env env, CXCursor *data) { delete data; });
        return result;
      },
      "nodeClang.getTranslationUnitCursor");

  return exports;
}

NODE_API_MODULE(nodeClang, Init);
