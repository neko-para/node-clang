#pragma once

#include <memory>

#include <clang-c/Index.h>
#include <napi.h>

#include "class/convert.h"
#include "class/instance.h"
#include "class/source_location.h"
#include "class/type.h"
#include "class/types.h"

struct [[clang::annotate("class")]] Cursor : public WrapBase<Cursor>
{
    static Napi::Function Init(Napi::Env env);

    Cursor(const Napi::CallbackInfo& info);

    nc_method static ConvertReturn<Cursor> null(Napi::Env env);
    nc_method bool isEqual(ConvertRef<Cursor> cursor);
    nc_method_as(isEqual) bool isEqualRelax(ConvertRef<Cursor> cursor, bool relax);
    nc_getter bool isNull();
    nc_getter unsigned getHash();
    nc_getter int getKind();
    nc_getter std::string getKindStr();
    nc_method static bool isDeclaration(Napi::Env env, int kind);
    nc_getter bool isInvalidDeclaration();
    nc_method static bool isReference(Napi::Env env, int kind);
    nc_method static bool isExpression(Napi::Env env, int kind);
    nc_method static bool isStatement(Napi::Env env, int kind);
    nc_method static bool isAttribute(Napi::Env env, int kind);
    nc_getter bool hasAttrs();
    nc_method static bool isInvalid(Napi::Env env, int kind);
    nc_method static bool isTranslationUnit(Napi::Env env, int kind);
    nc_method static bool isPreprocessing(Napi::Env env, int kind);
    nc_method static bool isUnexposed(Napi::Env env, int kind);
    nc_getter int getLinkage();
    nc_getter int getVisibility();
    nc_getter int getAvailability();
    nc_getter std::tuple<bool, std::string, bool, std::string, std::vector<PlatformAvailability>> getPlatformAvailability();
    nc_getter ConvertReturn<Cursor> getVarDeclInitializer();
    nc_getter int hasVarDeclGlobalStorage();
    nc_getter int hasVarDeclExternalStorage();
    nc_getter int getCursorLanguage();
    nc_getter_as(TLSKind) int getTLSKind();
    nc_getter std::optional<ConvertReturn<TranslationUnit>> getTranslateUnit();
    nc_getter ConvertReturn<Cursor> getLexicalParent();
    nc_getter ConvertReturn<Cursor> getSemanticParent();
    nc_getter std::optional<std::vector<ConvertReturn<Cursor>>> getOverriddenCursors();
    nc_getter std::optional<ConvertReturn<File>> getIncludedFile();
    nc_getter ConvertReturn<SourceLocation> getLocation();
    nc_getter ConvertReturn<SourceRange> getExtent();
    nc_getter ConvertReturn<Type> getType();
    nc_getter ConvertReturn<Type> getTypedefDeclUnderlyingType();
    nc_getter ConvertReturn<Type> getEnumDeclIntegerType();
    nc_getter long long getEnumConstantDeclValue();
    nc_getter unsigned long long getEnumConstantDeclUnsignedValue();
    nc_getter bool isBitField();
    nc_getter int getFieldDeclBitWidth();
    nc_getter int getNumArguments();
    nc_method ConvertReturn<Cursor> getArgument(unsigned index);
    nc_getter int getNumTemplateArguments();
    nc_method int getTemplateArgumentKind(unsigned index);
    nc_method ConvertReturn<Type> getTemplateArgumentType(unsigned index);
    nc_method long long getTemplateArgumentValue(unsigned index);
    nc_method unsigned long long getTemplateArgumentUnsignedValue(unsigned index);
    nc_getter bool isMacroFunctionLike();
    nc_getter bool isMacroBuiltin();
    nc_getter bool isFunctionInlined();
    nc_getter std::string getDeclObjCTypeEncoding();
    nc_getter ConvertReturn<Type> getCursorResultType();

    nc_getter std::string getSpelling();
    nc_method bool visitChildren(Napi::Function visitor);

    nc_getter std::string getMangling();
    nc_getter_as(CXXManglings) std::vector<std::string> getCXXManglings();
    nc_getter_as(ObjCManglings) std::vector<std::string> getObjCManglings();

    nc_getter bool CXXMethod_isStatic();

    nc_method std::string __dump();

    nc_inspect std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

    struct State
    {
        CXCursor data {};
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

struct [[clang::annotate("class")]] CursorSet : public WrapBase<CursorSet>
{
    static Napi::Function Init(Napi::Env env);

    CursorSet(const Napi::CallbackInfo& info);

    nc_method static ConvertReturn<CursorSet> create(Napi::Env env);
    nc_method bool contains(ConvertRef<Cursor> cursor);
    nc_method bool insert(ConvertRef<Cursor> cursor);

    struct State
    {
        Napi::Env env;
        CXCursorSet data {};

        State(Napi::Env env)
            : env(env) {};
        ~State();
    };

    std::shared_ptr<State> state {};

    static std::tuple<State*, Napi::Object> construct(Napi::Env env);
};

;
