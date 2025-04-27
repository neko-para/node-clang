#include "class/cursor.h"

#include <memory>

#include "class/convert.h"
#include "class/instance.h"
#include "class/source_location.h"
#include "class/type.h"
#include "enum.h"

Cursor::Cursor(const Napi::CallbackInfo& info)
    : WrapBase<Cursor>(info)
    , state(std::make_shared<State>())
{
}

ConvertReturn<Cursor> Cursor::null(Napi::Env env)
{
    auto [state, obj] = Cursor::construct(env);
    state->data = Instance::get(env).library->getNullCursor();
    return { obj };
}

bool Cursor::isEqual(ConvertRef<Cursor> cursor)
{
    return library()->equalCursors(state->data, cursor.data->state->data);
}

bool Cursor::isEqualRelax(ConvertRef<Cursor> cursor, bool relax)
{
    auto c1 = state->data;
    auto c2 = cursor.data->state->data;
    if (library()->isDeclaration(c1.kind)) {
        c1.data[1] = nullptr;
    }
    if (library()->isDeclaration(c2.kind)) {
        c2.data[1] = nullptr;
    }
    if (!(c1.kind == c2.kind && c1.data[1] == c2.data[1] && c1.data[2] == c2.data[2])) {
        return false;
    }
    if (relax) {
        return c1.data[0] == c2.data[0] || !c1.data[0] || !c2.data[0];
    }
    else {
        return c1.data[0] == c2.data[0];
    }
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

std::optional<ConvertReturn<TranslationUnit>> Cursor::getTranslateUnit()
{
    auto tu = library()->Cursor_getTranslationUnit(state->data);
    auto it = instance().translationUnits.find(tu);
    if (it == instance().translationUnits.end()) {
        return std::nullopt;
    }
    const auto& objref = it->second;
    try {
        return ConvertReturn<TranslationUnit> { objref.Value() };
    }
    catch (const Napi::Error& err) {
        return std::nullopt;
    }
}

ConvertReturn<Type> Cursor::getType()
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->getCursorType(state->data);
    return { obj };
}

ConvertReturn<Cursor> Cursor::getLexicalParent()
{
    auto [cstate, obj] = Cursor::construct(Env());
    cstate->data = library()->getCursorLexicalParent(state->data);
    return { obj };
}

ConvertReturn<Cursor> Cursor::getSemanticParent()
{
    auto [cstate, obj] = Cursor::construct(Env());
    cstate->data = library()->getCursorSemanticParent(state->data);
    return { obj };
}

ConvertReturn<SourceLocation> Cursor::getLocation()
{
    auto [sstate, obj] = SourceLocation::construct(Env());
    sstate->data = library()->getCursorLocation(state->data);
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
        Napi::Function visitor;
    } ctx = {
        visitor,
    };

    return library()->visitChildren(
        state->data,
        +[](CXCursor cursor, CXCursor parent, CXClientData client_data) -> CXChildVisitResult {
            auto ctx = reinterpret_cast<VisitCtx*>(client_data);
            auto env = ctx->visitor.Env();

            auto [cstate, cobj] = Cursor::construct(env);
            cstate->data = cursor;

            auto [pstate, pobj] = Cursor::construct(env);
            pstate->data = parent;

            auto res = ctx->visitor.Call({ cobj, pobj });
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

bool Cursor::CXXMethod_isStatic()
{
    return library()->CXXMethod_isStatic(state->data);
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
