#include "class/cursor.h"

#include <algorithm>
#include <iterator>
#include <memory>

#include "class/convert.h"
#include "class/instance.h"
#include "class/source_location.h"
#include "class/type.h"
#include "enum.h"
#include "clang-c/Index.h"

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

bool Cursor::isDeclaration(Napi::Env env, int kind)
{
    return Instance::get(env).library->isDeclaration(static_cast<CXCursorKind>(kind));
}

bool Cursor::isInvalidDeclaration()
{
    return library()->isInvalidDeclaration(state->data);
}

bool Cursor::isReference(Napi::Env env, int kind)
{
    return Instance::get(env).library->isReference(static_cast<CXCursorKind>(kind));
}

bool Cursor::isExpression(Napi::Env env, int kind)
{
    return Instance::get(env).library->isExpression(static_cast<CXCursorKind>(kind));
}

bool Cursor::isStatement(Napi::Env env, int kind)
{
    return Instance::get(env).library->isStatement(static_cast<CXCursorKind>(kind));
}

bool Cursor::isAttribute(Napi::Env env, int kind)
{
    return Instance::get(env).library->isAttribute(static_cast<CXCursorKind>(kind));
}

bool Cursor::hasAttrs()
{
    return library()->Cursor_hasAttrs(state->data);
}

bool Cursor::isInvalid(Napi::Env env, int kind)
{
    return Instance::get(env).library->isInvalid(static_cast<CXCursorKind>(kind));
}

bool Cursor::isTranslationUnit(Napi::Env env, int kind)
{
    return Instance::get(env).library->isTranslationUnit(static_cast<CXCursorKind>(kind));
}

bool Cursor::isPreprocessing(Napi::Env env, int kind)
{
    return Instance::get(env).library->isPreprocessing(static_cast<CXCursorKind>(kind));
}

bool Cursor::isUnexposed(Napi::Env env, int kind)
{
    return Instance::get(env).library->isUnexposed(static_cast<CXCursorKind>(kind));
}

int Cursor::getLinkage()
{
    return library()->getCursorLinkage(state->data);
}

int Cursor::getVisibility()
{
    return library()->getCursorVisibility(state->data);
}

int Cursor::getAvailability()
{
    return library()->getCursorAvailability(state->data);
}

std::tuple<bool, std::string, bool, std::string, std::vector<PlatformAvailability>> Cursor::getPlatformAvailability()
{
    auto size = library()->getCursorPlatformAvailability(state->data, nullptr, nullptr, nullptr, nullptr, nullptr, 0);
    std::vector<CXPlatformAvailability> data(size);
    int always_deprecated;
    CXString deprecated_msg;
    int always_unavailable;
    CXString unavailable_msg;
    library()->getCursorPlatformAvailability(
        state->data,
        &always_deprecated,
        &deprecated_msg,
        &always_unavailable,
        &unavailable_msg,
        size ? data.data() : nullptr,
        size);
    std::vector<PlatformAvailability> availability_info;
    availability_info.reserve(size);
    std::transform(
        data.begin(),
        data.end(),
        std::back_insert_iterator(availability_info),
        [&](CXPlatformAvailability& info) -> PlatformAvailability {
            PlatformAvailability result = {
                getStr(info.Platform, false),
                {
                    info.Introduced.Major,
                    info.Introduced.Minor,
                    info.Introduced.Subminor,
                },
                {
                    info.Deprecated.Major,
                    info.Deprecated.Minor,
                    info.Deprecated.Subminor,
                },
                {
                    info.Obsoleted.Major,
                    info.Obsoleted.Minor,
                    info.Obsoleted.Subminor,
                },
                (bool)info.Unavailable,
                getStr(info.Message, false),
            };
            library()->disposeCXPlatformAvailability(&info);
            return result;
        });
    return {
        (bool)always_deprecated, getStr(deprecated_msg), (bool)always_unavailable, getStr(unavailable_msg), availability_info,
    };
}

ConvertReturn<Cursor> Cursor::getVarDeclInitializer()
{
    auto [cstate, obj] = Cursor::construct(Env());
    cstate->data = library()->Cursor_getVarDeclInitializer(state->data);
    return { obj };
}

int Cursor::hasVarDeclGlobalStorage()
{
    return library()->Cursor_hasVarDeclGlobalStorage(state->data);
}

int Cursor::hasVarDeclExternalStorage()
{
    return library()->Cursor_hasVarDeclExternalStorage(state->data);
}

int Cursor::getCursorLanguage()
{
    return library()->getCursorLanguage(state->data);
}

int Cursor::getTLSKind()
{
    return library()->getCursorTLSKind(state->data);
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

std::optional<std::vector<ConvertReturn<Cursor>>> Cursor::getOverriddenCursors()
{
    CXCursor* cursors;
    unsigned size;
    library()->getOverriddenCursors(state->data, &cursors, &size);
    if (!cursors) {
        return std::nullopt;
    }
    std::vector<ConvertReturn<Cursor>> result;
    result.reserve(size);
    std::transform(cursors, cursors + size, std::back_insert_iterator(result), [&](const CXCursor& cursor) -> ConvertReturn<Cursor> {
        auto [cstate, obj] = Cursor::construct(Env());
        cstate->data = cursor;
        return { obj };
    });
    library()->disposeOverriddenCursors(cursors);
    return result;
}

std::optional<ConvertReturn<File>> Cursor::getIncludedFile()
{
    auto file = library()->getIncludedFile(state->data);
    if (!file) {
        return std::nullopt;
    }
    auto [fstate, obj] = File::construct(Env());
    fstate->data = file;
    return ConvertReturn<File> { obj };
}

ConvertReturn<SourceLocation> Cursor::getLocation()
{
    auto [sstate, obj] = SourceLocation::construct(Env());
    sstate->data = library()->getCursorLocation(state->data);
    return { obj };
}

ConvertReturn<SourceRange> Cursor::getExtent()
{
    auto [sstate, obj] = SourceRange::construct(Env());
    sstate->data = library()->getCursorExtent(state->data);
    return { obj };
}

ConvertReturn<Type> Cursor::getType()
{
    auto [tstate, obj] = Type::construct(Env());
    tstate->data = library()->getCursorType(state->data);
    return { obj };
}

long long Cursor::getEnumConstantDeclValue()
{
    return library()->getEnumConstantDeclValue(state->data);
}

std::string Cursor::getSpelling()
{
    return getStr(library()->getCursorSpelling(state->data));
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

std::string Cursor::getMangling()
{
    return getStr(library()->Cursor_getMangling(state->data));
}

std::vector<std::string> Cursor::getCXXManglings()
{
    auto lst = library()->Cursor_getCXXManglings(state->data);
    std::vector<std::string> result;
    result.reserve(lst->Count);
    std::transform(lst->Strings, lst->Strings + lst->Count, std::back_insert_iterator(result), [&](const CXString& str) -> std::string {
        return getStr(str, false);
    });
    library()->disposeStringSet(lst);
    return result;
}

std::vector<std::string> Cursor::getObjCManglings()
{
    auto lst = library()->Cursor_getObjCManglings(state->data);
    std::vector<std::string> result;
    result.reserve(lst->Count);
    std::transform(lst->Strings, lst->Strings + lst->Count, std::back_insert_iterator(result), [&](const CXString& str) -> std::string {
        return getStr(str, false);
    });
    library()->disposeStringSet(lst);
    return result;
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

CursorSet::CursorSet(const Napi::CallbackInfo& info)
    : WrapBase<CursorSet>(info)
    , state(std::make_shared<State>(Env()))
{
}

ConvertReturn<CursorSet> CursorSet::create(Napi::Env env)
{
    auto [state, obj] = CursorSet::construct(env);
    state->data = Instance::get(env).library->createCXCursorSet();
    return { obj };
}

bool CursorSet::contains(ConvertRef<Cursor> cursor)
{
    return library()->CXCursorSet_contains(state->data, cursor.data->state->data);
}

bool CursorSet::insert(ConvertRef<Cursor> cursor)
{
    return library()->CXCursorSet_insert(state->data, cursor.data->state->data);
}

CursorSet::State::~State()
{
    if (data) {
        Instance::get(env).library->disposeCXCursorSet(data);
    }
}
