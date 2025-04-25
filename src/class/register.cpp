#include <napi.h>

#include "class/cursor.h"
#include "class/file.h"
#include "class/global.h"
#include "class/index.h"
#include "class/instance.h"
#include "class/source_location.h"
#include "class/translation_unit.h"
#include "class/type.h"

Napi::Function Cursor::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CCursor",
        {
            InstanceAccessor(
                "CXXMethod_isStatic",
                &Cursor::dispatcher<"get CXXMethod_isStatic", &Cursor::CXXMethod_isStatic>,
                nullptr
            ),
            InstanceAccessor(
                "enumConstantDeclValue",
                &Cursor::dispatcher<"get enumConstantDeclValue", &Cursor::getEnumConstantDeclValue>,
                nullptr
            ),
            InstanceAccessor(
                "hash",
                &Cursor::dispatcher<"get hash", &Cursor::getHash>,
                nullptr
            ),
            InstanceAccessor(
                "isNull",
                &Cursor::dispatcher<"get isNull", &Cursor::isNull>,
                nullptr
            ),
            InstanceAccessor(
                "kind",
                &Cursor::dispatcher<"get kind", &Cursor::getKind>,
                nullptr
            ),
            InstanceAccessor(
                "kindStr",
                &Cursor::dispatcher<"get kindStr", &Cursor::getKindStr>,
                nullptr
            ),
            InstanceAccessor(
                "lexicalParent",
                &Cursor::dispatcher<"get lexicalParent", &Cursor::getLexicalParent>,
                nullptr
            ),
            InstanceAccessor(
                "location",
                &Cursor::dispatcher<"get location", &Cursor::getLocation>,
                nullptr
            ),
            InstanceAccessor(
                "semanticParent",
                &Cursor::dispatcher<"get semanticParent", &Cursor::getSemanticParent>,
                nullptr
            ),
            InstanceAccessor(
                "spelling",
                &Cursor::dispatcher<"get spelling", &Cursor::getSpelling>,
                nullptr
            ),
            InstanceAccessor(
                "translateUnit",
                &Cursor::dispatcher<"get translateUnit", &Cursor::getTranslateUnit>,
                nullptr
            ),
            InstanceAccessor(
                "type",
                &Cursor::dispatcher<"get type", &Cursor::getType>,
                nullptr
            ),
            InstanceMethod(
                "__dump",
                &Cursor::dispatcher<
                    "__dump",
                    &Cursor::__dump
                >
            ),
            InstanceMethod(
                "isEqual",
                &Cursor::dispatcher<
                    "isEqual",
                    &Cursor::isEqual,
                    &Cursor::isEqualRelax
                >
            ),
            InstanceMethod(
                "visitChildren",
                &Cursor::dispatcher<
                    "visitChildren",
                    &Cursor::visitChildren
                >
            ),
            StaticMethod(
                "null",
                &Cursor::dispatcherStatic<
                    "null",
                    &Cursor::null
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &Cursor::dispatcher<"nodejs inspect", &Cursor::nodejsInspect>),
        });
    Instance::get(env).cursorConstructor = Napi::Persistent(func);
    return func;
}

Napi::Function File::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CFile",
        {
            InstanceAccessor(
                "fileContents",
                &File::dispatcher<"get fileContents", &File::getFileContents>,
                nullptr
            ),
            InstanceAccessor(
                "fileName",
                &File::dispatcher<"get fileName", &File::getFileName>,
                nullptr
            ),
            InstanceAccessor(
                "fileTime",
                &File::dispatcher<"get fileTime", &File::getFileTime>,
                nullptr
            ),
            InstanceAccessor(
                "fileUniqueID",
                &File::dispatcher<"get fileUniqueID", &File::getFileUniqueID>,
                nullptr
            ),
            InstanceAccessor(
                "isMultipleIncludeGuarded",
                &File::dispatcher<"get isMultipleIncludeGuarded", &File::isMultipleIncludeGuarded>,
                nullptr
            ),
            InstanceAccessor(
                "realPathName",
                &File::dispatcher<"get realPathName", &File::getRealPathName>,
                nullptr
            ),
            InstanceMethod(
                "equal",
                &File::dispatcher<
                    "equal",
                    &File::equal
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &File::dispatcher<"nodejs inspect", &File::nodejsInspect>),
        });
    Instance::get(env).fileConstructor = Napi::Persistent(func);
    return func;
}

Napi::Function Global::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CGlobal",
        {
            StaticMethod(
                "buildSessionTimestamp",
                &Global::dispatcherStatic<
                    "buildSessionTimestamp",
                    &Global::buildSessionTimestamp
                >
            ),
        });
    Instance::get(env).globalConstructor = Napi::Persistent(func);
    return func;
}

Napi::Function Index::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CIndex",
        {
            InstanceAccessor(
                "globalOptions",
                &Index::dispatcher<"get globalOptions", &Index::getGlobalOptions>,
                nullptr
            ),
            InstanceMethod(
                "create",
                &Index::dispatcher<
                    "create",
                    &Index::create,
                    &Index::createIndexWithOptions
                >
            ),
            InstanceMethod(
                "createTranslationUnit",
                &Index::dispatcher<
                    "createTranslationUnit",
                    &Index::createTranslationUnit
                >
            ),
            InstanceMethod(
                "createTranslationUnitFromSourceFile",
                &Index::dispatcher<
                    "createTranslationUnitFromSourceFile",
                    &Index::createTranslationUnitFromSourceFile
                >
            ),
            InstanceMethod(
                "parseTranslationUnit",
                &Index::dispatcher<
                    "parseTranslationUnit",
                    &Index::parseTranslationUnit
                >
            ),
            InstanceMethod(
                "parseTranslationUnitFullArgv",
                &Index::dispatcher<
                    "parseTranslationUnitFullArgv",
                    &Index::parseTranslationUnitFullArgv
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &Index::dispatcher<"nodejs inspect", &Index::nodejsInspect>),
        });
    Instance::get(env).indexConstructor = Napi::Persistent(func);
    return func;
}

Napi::Function IndexOptions::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CIndexOptions",
        {
            InstanceAccessor(
                "displayDiagnostics",
                &IndexOptions::dispatcher<"get displayDiagnostics", &IndexOptions::getDisplayDiagnostics>,
                &IndexOptions::dispatcherSetter<"set displayDiagnostics", &IndexOptions::setDisplayDiagnostics>
            ),
            InstanceAccessor(
                "excludeDeclarationsFromPCH",
                &IndexOptions::dispatcher<"get excludeDeclarationsFromPCH", &IndexOptions::getExcludeDeclarationsFromPCH>,
                &IndexOptions::dispatcherSetter<"set excludeDeclarationsFromPCH", &IndexOptions::setExcludeDeclarationsFromPCH>
            ),
            InstanceAccessor(
                "invocationEmissionPath",
                &IndexOptions::dispatcher<"get invocationEmissionPath", &IndexOptions::getInvocationEmissionPath>,
                &IndexOptions::dispatcherSetter<"set invocationEmissionPath", &IndexOptions::setInvocationEmissionPath>
            ),
            InstanceAccessor(
                "preambleStoragePath",
                &IndexOptions::dispatcher<"get preambleStoragePath", &IndexOptions::getPreambleStoragePath>,
                &IndexOptions::dispatcherSetter<"set preambleStoragePath", &IndexOptions::setPreambleStoragePath>
            ),
            InstanceAccessor(
                "size",
                &IndexOptions::dispatcher<"get size", &IndexOptions::getSize>,
                &IndexOptions::dispatcherSetter<"set size", &IndexOptions::setSize>
            ),
            InstanceAccessor(
                "storePreamblesInMemory",
                &IndexOptions::dispatcher<"get storePreamblesInMemory", &IndexOptions::getStorePreamblesInMemory>,
                &IndexOptions::dispatcherSetter<"set storePreamblesInMemory", &IndexOptions::setStorePreamblesInMemory>
            ),
            InstanceAccessor(
                "threadBackgroundPriorityForEditing",
                &IndexOptions::dispatcher<"get threadBackgroundPriorityForEditing", &IndexOptions::getThreadBackgroundPriorityForEditing>,
                &IndexOptions::dispatcherSetter<"set threadBackgroundPriorityForEditing", &IndexOptions::setThreadBackgroundPriorityForEditing>
            ),
            InstanceAccessor(
                "threadBackgroundPriorityForIndexing",
                &IndexOptions::dispatcher<"get threadBackgroundPriorityForIndexing", &IndexOptions::getThreadBackgroundPriorityForIndexing>,
                &IndexOptions::dispatcherSetter<"set threadBackgroundPriorityForIndexing", &IndexOptions::setThreadBackgroundPriorityForIndexing>
            ),
        });
    Instance::get(env).indexOptionsConstructor = Napi::Persistent(func);
    return func;
}

Napi::Function SourceLocation::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CSourceLocation",
        {
            InstanceAccessor(
                "expansionLocation",
                &SourceLocation::dispatcher<"get expansionLocation", &SourceLocation::getExpansionLocation>,
                nullptr
            ),
            InstanceAccessor(
                "isFromMainFile",
                &SourceLocation::dispatcher<"get isFromMainFile", &SourceLocation::isFromMainFile>,
                nullptr
            ),
            InstanceAccessor(
                "isInSystemHeader",
                &SourceLocation::dispatcher<"get isInSystemHeader", &SourceLocation::isInSystemHeader>,
                nullptr
            ),
            InstanceAccessor(
                "presumedLocation",
                &SourceLocation::dispatcher<"get presumedLocation", &SourceLocation::getPresumedLocation>,
                nullptr
            ),
            InstanceMethod(
                "isBefore",
                &SourceLocation::dispatcher<
                    "isBefore",
                    &SourceLocation::isBefore
                >
            ),
            InstanceMethod(
                "isEqual",
                &SourceLocation::dispatcher<
                    "isEqual",
                    &SourceLocation::isEqual
                >
            ),
            StaticMethod(
                "null",
                &SourceLocation::dispatcherStatic<
                    "null",
                    &SourceLocation::null
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &SourceLocation::dispatcher<"nodejs inspect", &SourceLocation::nodejsInspect>),
        });
    Instance::get(env).sourceLocationConstructor = Napi::Persistent(func);
    return func;
}

Napi::Function TranslationUnit::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CTranslationUnit",
        {
            InstanceAccessor(
                "cursor",
                &TranslationUnit::dispatcher<"get cursor", &TranslationUnit::getCursor>,
                nullptr
            ),
            InstanceAccessor(
                "spelling",
                &TranslationUnit::dispatcher<"get spelling", &TranslationUnit::getSpelling>,
                nullptr
            ),
            InstanceMethod(
                "getFile",
                &TranslationUnit::dispatcher<
                    "getFile",
                    &TranslationUnit::getFile
                >
            ),
            InstanceMethod(
                "reparse",
                &TranslationUnit::dispatcher<
                    "reparse",
                    &TranslationUnit::reparse
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &TranslationUnit::dispatcher<"nodejs inspect", &TranslationUnit::nodejsInspect>),
        });
    Instance::get(env).translationUnitConstructor = Napi::Persistent(func);
    return func;
}

Napi::Function Type::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CType",
        {
            InstanceAccessor(
                "kind",
                &Type::dispatcher<"get kind", &Type::getKind>,
                nullptr
            ),
            InstanceAccessor(
                "kindStr",
                &Type::dispatcher<"get kindStr", &Type::getKindStr>,
                nullptr
            ),
            InstanceAccessor(
                "spelling",
                &Type::dispatcher<"get spelling", &Type::getSpelling>,
                nullptr
            ),
            InstanceMethod(
                "isEqual",
                &Type::dispatcher<
                    "isEqual",
                    &Type::isEqual
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &Type::dispatcher<"nodejs inspect", &Type::nodejsInspect>),
        });
    Instance::get(env).typeConstructor = Napi::Persistent(func);
    return func;
}
