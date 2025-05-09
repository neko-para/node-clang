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

    [[clang::annotate("method")]] static ConvertReturn<Cursor> null(Napi::Env env);
    [[clang::annotate("method")]] bool isEqual(ConvertRef<Cursor> cursor);
    [[clang::annotate("method:isEqual")]] bool isEqualRelax(ConvertRef<Cursor> cursor, bool relax);
    [[clang::annotate("getter")]] bool isNull();
    [[clang::annotate("getter")]] unsigned getHash();
    [[clang::annotate("getter")]] int getKind();
    [[clang::annotate("getter")]] std::string getKindStr();
    [[clang::annotate("method")]] static bool isDeclaration(Napi::Env env, int kind);
    [[clang::annotate("getter")]] bool isInvalidDeclaration();
    [[clang::annotate("method")]] static bool isReference(Napi::Env env, int kind);
    [[clang::annotate("method")]] static bool isExpression(Napi::Env env, int kind);
    [[clang::annotate("method")]] static bool isStatement(Napi::Env env, int kind);
    [[clang::annotate("method")]] static bool isAttribute(Napi::Env env, int kind);
    [[clang::annotate("getter")]] bool hasAttrs();
    [[clang::annotate("method")]] static bool isInvalid(Napi::Env env, int kind);
    [[clang::annotate("method")]] static bool isTranslationUnit(Napi::Env env, int kind);
    [[clang::annotate("method")]] static bool isPreprocessing(Napi::Env env, int kind);
    [[clang::annotate("method")]] static bool isUnexposed(Napi::Env env, int kind);
    [[clang::annotate("getter")]] int getLinkage();
    [[clang::annotate("getter")]] int getVisibility();
    [[clang::annotate("getter")]] int getAvailability();
    [[clang::annotate("getter")]] std::tuple<bool, std::string, bool, std::string, std::vector<PlatformAvailability>>
        getPlatformAvailability();
    [[clang::annotate("getter")]] ConvertReturn<Cursor> getVarDeclInitializer();
    [[clang::annotate("getter")]] int hasVarDeclGlobalStorage();
    [[clang::annotate("getter")]] int hasVarDeclExternalStorage();
    [[clang::annotate("getter")]] int getCursorLanguage();
    [[clang::annotate("getter:TLSKind")]] int getTLSKind();
    [[clang::annotate("getter")]] std::optional<ConvertReturn<TranslationUnit>> getTranslateUnit();
    [[clang::annotate("getter")]] ConvertReturn<Cursor> getLexicalParent();
    [[clang::annotate("getter")]] ConvertReturn<Cursor> getSemanticParent();
    [[clang::annotate("getter")]] std::optional<std::vector<ConvertReturn<Cursor>>> getOverriddenCursors();
    [[clang::annotate("getter")]] std::optional<ConvertReturn<File>> getIncludedFile();
    [[clang::annotate("getter")]] ConvertReturn<SourceLocation> getLocation();
    [[clang::annotate("getter")]] ConvertReturn<SourceRange> getExtent();
    [[clang::annotate("getter")]] ConvertReturn<Type> getType();
    [[clang::annotate("getter")]] ConvertReturn<Type> getTypedefDeclUnderlyingType();
    [[clang::annotate("getter")]] ConvertReturn<Type> getEnumDeclIntegerType();
    [[clang::annotate("getter")]] long long getEnumConstantDeclValue();
    [[clang::annotate("getter")]] unsigned long long getEnumConstantDeclUnsignedValue();
    [[clang::annotate("getter")]] bool isBitField();
    [[clang::annotate("getter")]] int getFieldDeclBitWidth();
    [[clang::annotate("getter")]] int getNumArguments();
    [[clang::annotate("method")]] ConvertReturn<Cursor> getArgument(unsigned index);
    [[clang::annotate("getter")]] int getNumTemplateArguments();
    [[clang::annotate("method")]] int getTemplateArgumentKind(unsigned index);
    [[clang::annotate("method")]] ConvertReturn<Type> getTemplateArgumentType(unsigned index);
    [[clang::annotate("method")]] long long getTemplateArgumentValue(unsigned index);
    [[clang::annotate("method")]] unsigned long long getTemplateArgumentUnsignedValue(unsigned index);
    [[clang::annotate("getter")]] bool isMacroFunctionLike();
    [[clang::annotate("getter")]] bool isMacroBuiltin();
    [[clang::annotate("getter")]] bool isFunctionInlined();
    [[clang::annotate("getter")]] std::string getDeclObjCTypeEncoding();

    [[clang::annotate("getter")]] std::string getSpelling();
    [[clang::annotate("method")]] bool visitChildren(Napi::Function visitor);

    [[clang::annotate("getter")]] std::string getMangling();
    [[clang::annotate("getter:CXXManglings")]] std::vector<std::string> getCXXManglings();
    [[clang::annotate("getter:ObjCManglings")]] std::vector<std::string> getObjCManglings();

    [[clang::annotate("getter")]] bool CXXMethod_isStatic();

    [[clang::annotate("method")]] std::string __dump();

    [[clang::annotate("inspect")]] std::string nodejsInspect(ConvertAny depth, ConvertAny opts, ConvertAny inspect);

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

    [[clang::annotate("method")]] static ConvertReturn<CursorSet> create(Napi::Env env);
    [[clang::annotate("method")]] bool contains(ConvertRef<Cursor> cursor);
    [[clang::annotate("method")]] bool insert(ConvertRef<Cursor> cursor);

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
