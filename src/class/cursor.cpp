#include "cursor.h"

#include <memory>

#include "../api/enum.h"
#include "convert.h"
#include "instance.h"
#include "type.h"
#include "clang-c/Index.h"

Napi::Function Cursor::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CCursor",
        { InstanceMethod("equal", &Cursor::dispatcher<"equal", &Cursor::equal>),
          InstanceAccessor("isNull", &Cursor::dispatcher<"get isNull", &Cursor::isNull>, nullptr),
          InstanceAccessor("hash", &Cursor::dispatcher<"get hash", &Cursor::getHash>, nullptr),
          InstanceAccessor("kind", &Cursor::dispatcher<"get kind", &Cursor::getKind>, nullptr),
          InstanceAccessor("spelling", &Cursor::dispatcher<"get spelling", &Cursor::getSpelling>, nullptr),
          InstanceAccessor("translateUnit", &Cursor::dispatcher<"get translateUnit", &Cursor::getTranslateUnit>, nullptr),
          InstanceAccessor("type", &Cursor::dispatcher<"get type", &Cursor::getType>, nullptr),
          InstanceAccessor(
              "enumConstantDeclValue",
              &Cursor::dispatcher<"get enumConstantDeclValue", &Cursor::getEnumConstantDeclValue>,
              nullptr),
          InstanceMethod("visitChildren", &Cursor::dispatcher<"visitChildren", &Cursor::visitChildren>),

          InstanceMethod(
              Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
              &Cursor::dispatcher<"nodejs inspect", &Cursor::nodejsInspect>) });
    Instance::get(env).cursorConstructor = Napi::Persistent(func);
    return func;
}

Cursor::Cursor(const Napi::CallbackInfo& info)
    : WrapBase<Cursor>(info)
    , state(std::make_shared<State>())
{
}

bool Cursor::equal(ConvertRef<Cursor> cursor)
{
    return library()->equalCursors(state->data, cursor.data->state->data);
}

bool Cursor::isNull()
{
    return library()->Cursor_isNull(state->data);
}

unsigned Cursor::getHash()
{
    return library()->hashCursor(state->data);
}

int Cursor::getKind()
{
    return library()->getCursorKind(state->data);
}

std::string Cursor::getSpelling()
{
    return getStr(library()->getCursorSpelling(state->data));
}

ConvertReturn<TranslationUnit> Cursor::getTranslateUnit()
{
    return { state->tu.Value() };
}

ConvertReturn<Type> Cursor::getType()
{
    auto obj = instance().typeConstructor.New({});
    Napi::ObjectWrap<Type>::Unwrap(obj)->state->data = library()->getCursorType(state->data);
    return { obj };
}

long long Cursor::getEnumConstantDeclValue()
{
    return library()->getEnumConstantDeclValue(state->data);
}

bool Cursor::visitChildren(Napi::Function visitor)
{
    struct VisitCtx
    {
        Napi::Object tu;
        Napi::Function visitor;
    } ctx = {
        state->tu.Value(),
        visitor,
    };

    return library()->visitChildren(
        state->data,
        +[](CXCursor cursor, CXCursor parent, CXClientData client_data) -> CXChildVisitResult {
            auto ctx = reinterpret_cast<VisitCtx*>(client_data);
            auto env = ctx->visitor.Env();

            auto cursorObj = Instance::get(env).cursorConstructor.New({});
            auto cst = Napi::ObjectWrap<Cursor>::Unwrap(cursorObj)->state;
            cst->tu = Napi::Persistent(ctx->tu);
            cst->data = cursor;

            auto pcursorObj = Instance::get(env).cursorConstructor.New({});
            auto pcst = Napi::ObjectWrap<Cursor>::Unwrap(pcursorObj)->state;
            pcst->tu = Napi::Persistent(ctx->tu);
            pcst->data = parent;

            auto res = ctx->visitor.Call({ cursorObj, pcursorObj });
            try {
                return static_cast<CXChildVisitResult>(Convert<int>::from_value<0>(res));
            }
            catch (const ConvertFailed& err) {
                Napi::Error::New(env, err.error.c_str()).ThrowAsJavaScriptException();
                return CXChildVisit_Break;
            }
        },
        &ctx);
}

std::string Cursor::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    if (!isNull()) {
        auto kind = getKind();
        auto iter = cursorKind_enum2str.find(static_cast<CXCursorKind>(kind));
        return std::format("CCursor {{ {}({}) }}", getSpelling(), iter == cursorKind_enum2str.end() ? std::to_string(kind) : iter->second);
    }
    else {
        return "CCursor { null }";
    }
}
