#include "class/cursor.h"

#include <memory>

#include "class/convert.h"
#include "class/instance.h"
#include "class/type.h"
#include "enum.h"

Napi::Function Cursor::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CCursor",
        { InstanceMethod("equal", &Cursor::dispatcher<"equal", &Cursor::equal>),
          InstanceAccessor("isNull", &Cursor::dispatcher<"get isNull", &Cursor::isNull>, nullptr),
          InstanceAccessor("hash", &Cursor::dispatcher<"get hash", &Cursor::getHash>, nullptr),
          InstanceAccessor("kind", &Cursor::dispatcher<"get kind", &Cursor::getKind>, nullptr),
          InstanceAccessor("kindStr", &Cursor::dispatcher<"get kindStr", &Cursor::getKindStr>, nullptr),
          InstanceAccessor("spelling", &Cursor::dispatcher<"get spelling", &Cursor::getSpelling>, nullptr),
          InstanceAccessor("translateUnit", &Cursor::dispatcher<"get translateUnit", &Cursor::getTranslateUnit>, nullptr),
          InstanceAccessor("type", &Cursor::dispatcher<"get type", &Cursor::getType>, nullptr),
          InstanceAccessor(
              "enumConstantDeclValue",
              &Cursor::dispatcher<"get enumConstantDeclValue", &Cursor::getEnumConstantDeclValue>,
              nullptr),
          InstanceMethod("visitChildren", &Cursor::dispatcher<"visitChildren", &Cursor::visitChildren>),

          InstanceMethod("__dump", &Cursor::dispatcher<"__dump", &Cursor::__dump>),

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

std::string Cursor::getKindStr()
{
    auto kind = getKind();
    auto iter = cursorKind_enum2str.find(static_cast<CXCursorKind>(kind));
    return iter == cursorKind_enum2str.end() ? std::to_string(kind) : iter->second;
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

std::string Cursor::__dump()
{
    return std::format(
        "{} {} {} {} {}",
        (int)state->data.kind,
        state->data.xdata,
        reinterpret_cast<size_t>(state->data.data[0]),
        reinterpret_cast<size_t>(state->data.data[1]),
        reinterpret_cast<size_t>(state->data.data[2]));
}

std::string Cursor::nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect)
{
    if (!isNull()) {
        return std::format("CCursor {{ {}({}) }}", getSpelling(), getKindStr());
    }
    else {
        return "CCursor { null }";
    }
}
