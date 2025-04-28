#include <napi.h>

#include "class/build_system.h"
#include "class/cursor.h"
#include "class/diagnostic.h"
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
                "availability",
                &Cursor::dispatcher<"get availability", &Cursor::getAvailability>,
                nullptr
            ),
            InstanceAccessor(
                "cursorLanguage",
                &Cursor::dispatcher<"get cursorLanguage", &Cursor::getCursorLanguage>,
                nullptr
            ),
            InstanceAccessor(
                "CXXManglings",
                &Cursor::dispatcher<"get CXXManglings", &Cursor::getCXXManglings>,
                nullptr
            ),
            InstanceAccessor(
                "CXXMethod_isStatic",
                &Cursor::dispatcher<"get CXXMethod_isStatic", &Cursor::CXXMethod_isStatic>,
                nullptr
            ),
            InstanceAccessor(
                "declObjCTypeEncoding",
                &Cursor::dispatcher<"get declObjCTypeEncoding", &Cursor::getDeclObjCTypeEncoding>,
                nullptr
            ),
            InstanceAccessor(
                "enumConstantDeclUnsignedValue",
                &Cursor::dispatcher<"get enumConstantDeclUnsignedValue", &Cursor::getEnumConstantDeclUnsignedValue>,
                nullptr
            ),
            InstanceAccessor(
                "enumConstantDeclValue",
                &Cursor::dispatcher<"get enumConstantDeclValue", &Cursor::getEnumConstantDeclValue>,
                nullptr
            ),
            InstanceAccessor(
                "enumDeclIntegerType",
                &Cursor::dispatcher<"get enumDeclIntegerType", &Cursor::getEnumDeclIntegerType>,
                nullptr
            ),
            InstanceAccessor(
                "extent",
                &Cursor::dispatcher<"get extent", &Cursor::getExtent>,
                nullptr
            ),
            InstanceAccessor(
                "fieldDeclBitWidth",
                &Cursor::dispatcher<"get fieldDeclBitWidth", &Cursor::getFieldDeclBitWidth>,
                nullptr
            ),
            InstanceAccessor(
                "hasAttrs",
                &Cursor::dispatcher<"get hasAttrs", &Cursor::hasAttrs>,
                nullptr
            ),
            InstanceAccessor(
                "hash",
                &Cursor::dispatcher<"get hash", &Cursor::getHash>,
                nullptr
            ),
            InstanceAccessor(
                "hasVarDeclExternalStorage",
                &Cursor::dispatcher<"get hasVarDeclExternalStorage", &Cursor::hasVarDeclExternalStorage>,
                nullptr
            ),
            InstanceAccessor(
                "hasVarDeclGlobalStorage",
                &Cursor::dispatcher<"get hasVarDeclGlobalStorage", &Cursor::hasVarDeclGlobalStorage>,
                nullptr
            ),
            InstanceAccessor(
                "includedFile",
                &Cursor::dispatcher<"get includedFile", &Cursor::getIncludedFile>,
                nullptr
            ),
            InstanceAccessor(
                "isBitField",
                &Cursor::dispatcher<"get isBitField", &Cursor::isBitField>,
                nullptr
            ),
            InstanceAccessor(
                "isFunctionInlined",
                &Cursor::dispatcher<"get isFunctionInlined", &Cursor::isFunctionInlined>,
                nullptr
            ),
            InstanceAccessor(
                "isInvalidDeclaration",
                &Cursor::dispatcher<"get isInvalidDeclaration", &Cursor::isInvalidDeclaration>,
                nullptr
            ),
            InstanceAccessor(
                "isMacroBuiltin",
                &Cursor::dispatcher<"get isMacroBuiltin", &Cursor::isMacroBuiltin>,
                nullptr
            ),
            InstanceAccessor(
                "isMacroFunctionLike",
                &Cursor::dispatcher<"get isMacroFunctionLike", &Cursor::isMacroFunctionLike>,
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
                "linkage",
                &Cursor::dispatcher<"get linkage", &Cursor::getLinkage>,
                nullptr
            ),
            InstanceAccessor(
                "location",
                &Cursor::dispatcher<"get location", &Cursor::getLocation>,
                nullptr
            ),
            InstanceAccessor(
                "mangling",
                &Cursor::dispatcher<"get mangling", &Cursor::getMangling>,
                nullptr
            ),
            InstanceAccessor(
                "numArguments",
                &Cursor::dispatcher<"get numArguments", &Cursor::getNumArguments>,
                nullptr
            ),
            InstanceAccessor(
                "numTemplateArguments",
                &Cursor::dispatcher<"get numTemplateArguments", &Cursor::getNumTemplateArguments>,
                nullptr
            ),
            InstanceAccessor(
                "ObjCManglings",
                &Cursor::dispatcher<"get ObjCManglings", &Cursor::getObjCManglings>,
                nullptr
            ),
            InstanceAccessor(
                "overriddenCursors",
                &Cursor::dispatcher<"get overriddenCursors", &Cursor::getOverriddenCursors>,
                nullptr
            ),
            InstanceAccessor(
                "platformAvailability",
                &Cursor::dispatcher<"get platformAvailability", &Cursor::getPlatformAvailability>,
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
                "TLSKind",
                &Cursor::dispatcher<"get TLSKind", &Cursor::getTLSKind>,
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
            InstanceAccessor(
                "typedefDeclUnderlyingType",
                &Cursor::dispatcher<"get typedefDeclUnderlyingType", &Cursor::getTypedefDeclUnderlyingType>,
                nullptr
            ),
            InstanceAccessor(
                "varDeclInitializer",
                &Cursor::dispatcher<"get varDeclInitializer", &Cursor::getVarDeclInitializer>,
                nullptr
            ),
            InstanceAccessor(
                "visibility",
                &Cursor::dispatcher<"get visibility", &Cursor::getVisibility>,
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
                "getArgument",
                &Cursor::dispatcher<
                    "getArgument",
                    &Cursor::getArgument
                >
            ),
            InstanceMethod(
                "getTemplateArgumentKind",
                &Cursor::dispatcher<
                    "getTemplateArgumentKind",
                    &Cursor::getTemplateArgumentKind
                >
            ),
            InstanceMethod(
                "getTemplateArgumentType",
                &Cursor::dispatcher<
                    "getTemplateArgumentType",
                    &Cursor::getTemplateArgumentType
                >
            ),
            InstanceMethod(
                "getTemplateArgumentUnsignedValue",
                &Cursor::dispatcher<
                    "getTemplateArgumentUnsignedValue",
                    &Cursor::getTemplateArgumentUnsignedValue
                >
            ),
            InstanceMethod(
                "getTemplateArgumentValue",
                &Cursor::dispatcher<
                    "getTemplateArgumentValue",
                    &Cursor::getTemplateArgumentValue
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
                "isAttribute",
                &Cursor::dispatcherStatic<
                    "isAttribute",
                    &Cursor::isAttribute
                >
            ),
            StaticMethod(
                "isDeclaration",
                &Cursor::dispatcherStatic<
                    "isDeclaration",
                    &Cursor::isDeclaration
                >
            ),
            StaticMethod(
                "isExpression",
                &Cursor::dispatcherStatic<
                    "isExpression",
                    &Cursor::isExpression
                >
            ),
            StaticMethod(
                "isInvalid",
                &Cursor::dispatcherStatic<
                    "isInvalid",
                    &Cursor::isInvalid
                >
            ),
            StaticMethod(
                "isPreprocessing",
                &Cursor::dispatcherStatic<
                    "isPreprocessing",
                    &Cursor::isPreprocessing
                >
            ),
            StaticMethod(
                "isReference",
                &Cursor::dispatcherStatic<
                    "isReference",
                    &Cursor::isReference
                >
            ),
            StaticMethod(
                "isStatement",
                &Cursor::dispatcherStatic<
                    "isStatement",
                    &Cursor::isStatement
                >
            ),
            StaticMethod(
                "isTranslationUnit",
                &Cursor::dispatcherStatic<
                    "isTranslationUnit",
                    &Cursor::isTranslationUnit
                >
            ),
            StaticMethod(
                "isUnexposed",
                &Cursor::dispatcherStatic<
                    "isUnexposed",
                    &Cursor::isUnexposed
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

std::tuple<Cursor::State*, Napi::Object> Cursor::construct(Napi::Env env)
{
    auto obj = Instance::get(env).cursorConstructor.New({});
    auto state = Napi::ObjectWrap<Cursor>::Unwrap(obj)->state;
    return { state.get(), obj };
}

Napi::Function CursorSet::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CCursorSet",
        {
            InstanceMethod(
                "contains",
                &CursorSet::dispatcher<
                    "contains",
                    &CursorSet::contains
                >
            ),
            InstanceMethod(
                "insert",
                &CursorSet::dispatcher<
                    "insert",
                    &CursorSet::insert
                >
            ),
            StaticMethod(
                "create",
                &CursorSet::dispatcherStatic<
                    "create",
                    &CursorSet::create
                >
            ),
        });
    Instance::get(env).cursorSetConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<CursorSet::State*, Napi::Object> CursorSet::construct(Napi::Env env)
{
    auto obj = Instance::get(env).cursorSetConstructor.New({});
    auto state = Napi::ObjectWrap<CursorSet>::Unwrap(obj)->state;
    return { state.get(), obj };
}

Napi::Function Diagnostic::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CDiagnostic",
        {
            InstanceAccessor(
                "category",
                &Diagnostic::dispatcher<"get category", &Diagnostic::getCategory>,
                nullptr
            ),
            InstanceAccessor(
                "categoryText",
                &Diagnostic::dispatcher<"get categoryText", &Diagnostic::getCategoryText>,
                nullptr
            ),
            InstanceAccessor(
                "childDiagnostics",
                &Diagnostic::dispatcher<"get childDiagnostics", &Diagnostic::getChildDiagnostics>,
                nullptr
            ),
            InstanceAccessor(
                "location",
                &Diagnostic::dispatcher<"get location", &Diagnostic::getLocation>,
                nullptr
            ),
            InstanceAccessor(
                "numFixIts",
                &Diagnostic::dispatcher<"get numFixIts", &Diagnostic::getNumFixIts>,
                nullptr
            ),
            InstanceAccessor(
                "numRanges",
                &Diagnostic::dispatcher<"get numRanges", &Diagnostic::getNumRanges>,
                nullptr
            ),
            InstanceAccessor(
                "option",
                &Diagnostic::dispatcher<"get option", &Diagnostic::getOption>,
                nullptr
            ),
            InstanceAccessor(
                "severity",
                &Diagnostic::dispatcher<"get severity", &Diagnostic::getSeverity>,
                nullptr
            ),
            InstanceAccessor(
                "spelling",
                &Diagnostic::dispatcher<"get spelling", &Diagnostic::getSpelling>,
                nullptr
            ),
            InstanceMethod(
                "format",
                &Diagnostic::dispatcher<
                    "format",
                    &Diagnostic::format
                >
            ),
            InstanceMethod(
                "getFixIt",
                &Diagnostic::dispatcher<
                    "getFixIt",
                    &Diagnostic::getFixIt
                >
            ),
            InstanceMethod(
                "getRange",
                &Diagnostic::dispatcher<
                    "getRange",
                    &Diagnostic::getRange
                >
            ),
            StaticMethod(
                "defaultDisplayOptions",
                &Diagnostic::dispatcherStatic<
                    "defaultDisplayOptions",
                    &Diagnostic::defaultDisplayOptions
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &Diagnostic::dispatcher<"nodejs inspect", &Diagnostic::nodejsInspect>),
        });
    Instance::get(env).diagnosticConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<Diagnostic::State*, Napi::Object> Diagnostic::construct(Napi::Env env)
{
    auto obj = Instance::get(env).diagnosticConstructor.New({});
    auto state = Napi::ObjectWrap<Diagnostic>::Unwrap(obj)->state;
    return { state.get(), obj };
}

Napi::Function DiagnosticSet::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CDiagnosticSet",
        {
            InstanceAccessor(
                "length",
                &DiagnosticSet::dispatcher<"get length", &DiagnosticSet::getLength>,
                nullptr
            ),
            InstanceMethod(
                "getDiagnostic",
                &DiagnosticSet::dispatcher<
                    "getDiagnostic",
                    &DiagnosticSet::getDiagnostic
                >
            ),
            StaticMethod(
                "load",
                &DiagnosticSet::dispatcherStatic<
                    "load",
                    &DiagnosticSet::load
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &DiagnosticSet::dispatcher<"nodejs inspect", &DiagnosticSet::nodejsInspect>),
        });
    Instance::get(env).diagnosticSetConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<DiagnosticSet::State*, Napi::Object> DiagnosticSet::construct(Napi::Env env)
{
    auto obj = Instance::get(env).diagnosticSetConstructor.New({});
    auto state = Napi::ObjectWrap<DiagnosticSet>::Unwrap(obj)->state;
    return { state.get(), obj };
}

Napi::Function File::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CFile",
        {
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
                "getFileContents",
                &File::dispatcher<
                    "getFileContents",
                    &File::getFileContents
                >
            ),
            InstanceMethod(
                "getLocation",
                &File::dispatcher<
                    "getLocation",
                    &File::getLocation,
                    &File::getLocationForOffset
                >
            ),
            InstanceMethod(
                "isMultipleIncludeGuarded",
                &File::dispatcher<
                    "isMultipleIncludeGuarded",
                    &File::isMultipleIncludeGuarded
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &File::dispatcher<"nodejs inspect", &File::nodejsInspect>),
        });
    Instance::get(env).fileConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<File::State*, Napi::Object> File::construct(Napi::Env env)
{
    auto obj = Instance::get(env).fileConstructor.New({});
    auto state = Napi::ObjectWrap<File>::Unwrap(obj)->state;
    return { state.get(), obj };
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
            StaticMethod(
                "create",
                &Index::dispatcherStatic<
                    "create",
                    &Index::create,
                    &Index::createIndexWithOptions
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &Index::dispatcher<"nodejs inspect", &Index::nodejsInspect>),
        });
    Instance::get(env).indexConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<Index::State*, Napi::Object> Index::construct(Napi::Env env)
{
    auto obj = Instance::get(env).indexConstructor.New({});
    auto state = Napi::ObjectWrap<Index>::Unwrap(obj)->state;
    return { state.get(), obj };
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

Napi::Function ModuleMapDescriptor::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CModuleMapDescriptor",
        {
            InstanceAccessor(
                "frameworkModuleName",
                nullptr,
                &ModuleMapDescriptor::dispatcherSetter<"set frameworkModuleName", &ModuleMapDescriptor::setFrameworkModuleName>
            ),
            InstanceAccessor(
                "umbrellaHeader",
                nullptr,
                &ModuleMapDescriptor::dispatcherSetter<"set umbrellaHeader", &ModuleMapDescriptor::setUmbrellaHeader>
            ),
            InstanceMethod(
                "writeToBuffer",
                &ModuleMapDescriptor::dispatcher<
                    "writeToBuffer",
                    &ModuleMapDescriptor::writeToBuffer
                >
            ),
            StaticMethod(
                "create",
                &ModuleMapDescriptor::dispatcherStatic<
                    "create",
                    &ModuleMapDescriptor::create
                >
            ),
        });
    Instance::get(env).moduleMapDescriptorConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<ModuleMapDescriptor::State*, Napi::Object> ModuleMapDescriptor::construct(Napi::Env env)
{
    auto obj = Instance::get(env).moduleMapDescriptorConstructor.New({});
    auto state = Napi::ObjectWrap<ModuleMapDescriptor>::Unwrap(obj)->state;
    return { state.get(), obj };
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
                "fileLocation",
                &SourceLocation::dispatcher<"get fileLocation", &SourceLocation::getFileLocation>,
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
            InstanceAccessor(
                "spellingLocation",
                &SourceLocation::dispatcher<"get spellingLocation", &SourceLocation::getSpellingLocation>,
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

std::tuple<SourceLocation::State*, Napi::Object> SourceLocation::construct(Napi::Env env)
{
    auto obj = Instance::get(env).sourceLocationConstructor.New({});
    auto state = Napi::ObjectWrap<SourceLocation>::Unwrap(obj)->state;
    return { state.get(), obj };
}

Napi::Function SourceRange::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CSourceRange",
        {
            InstanceAccessor(
                "end",
                &SourceRange::dispatcher<"get end", &SourceRange::getEnd>,
                nullptr
            ),
            InstanceAccessor(
                "isNull",
                &SourceRange::dispatcher<"get isNull", &SourceRange::isNull>,
                nullptr
            ),
            InstanceAccessor(
                "start",
                &SourceRange::dispatcher<"get start", &SourceRange::getStart>,
                nullptr
            ),
            InstanceMethod(
                "isEqual",
                &SourceRange::dispatcher<
                    "isEqual",
                    &SourceRange::isEqual
                >
            ),
            StaticMethod(
                "create",
                &SourceRange::dispatcherStatic<
                    "create",
                    &SourceRange::create
                >
            ),
            StaticMethod(
                "null",
                &SourceRange::dispatcherStatic<
                    "null",
                    &SourceRange::null
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &SourceRange::dispatcher<"nodejs inspect", &SourceRange::nodejsInspect>),
        });
    Instance::get(env).sourceRangeConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<SourceRange::State*, Napi::Object> SourceRange::construct(Napi::Env env)
{
    auto obj = Instance::get(env).sourceRangeConstructor.New({});
    auto state = Napi::ObjectWrap<SourceRange>::Unwrap(obj)->state;
    return { state.get(), obj };
}

Napi::Function TranslationUnit::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CTranslationUnit",
        {
            InstanceAccessor(
                "allSkippedRanges",
                &TranslationUnit::dispatcher<"get allSkippedRanges", &TranslationUnit::getAllSkippedRanges>,
                nullptr
            ),
            InstanceAccessor(
                "cursor",
                &TranslationUnit::dispatcher<"get cursor", &TranslationUnit::getCursor>,
                nullptr
            ),
            InstanceAccessor(
                "defaultReparseOptions",
                &TranslationUnit::dispatcher<"get defaultReparseOptions", &TranslationUnit::getDefaultReparseOptions>,
                nullptr
            ),
            InstanceAccessor(
                "defaultSaveOptions",
                &TranslationUnit::dispatcher<"get defaultSaveOptions", &TranslationUnit::getDefaultSaveOptions>,
                nullptr
            ),
            InstanceAccessor(
                "diagnosticSet",
                &TranslationUnit::dispatcher<"get diagnosticSet", &TranslationUnit::getDiagnosticSet>,
                nullptr
            ),
            InstanceAccessor(
                "numDiagnostics",
                &TranslationUnit::dispatcher<"get numDiagnostics", &TranslationUnit::getNumDiagnostics>,
                nullptr
            ),
            InstanceAccessor(
                "resourceUsage",
                &TranslationUnit::dispatcher<"get resourceUsage", &TranslationUnit::getResourceUsage>,
                nullptr
            ),
            InstanceAccessor(
                "spelling",
                &TranslationUnit::dispatcher<"get spelling", &TranslationUnit::getSpelling>,
                nullptr
            ),
            InstanceAccessor(
                "targetInfo",
                &TranslationUnit::dispatcher<"get targetInfo", &TranslationUnit::getTargetInfo>,
                nullptr
            ),
            InstanceMethod(
                "getCursor",
                &TranslationUnit::dispatcher<
                    "getCursor",
                    &TranslationUnit::getCursorForLocation
                >
            ),
            InstanceMethod(
                "getDiagnostic",
                &TranslationUnit::dispatcher<
                    "getDiagnostic",
                    &TranslationUnit::getDiagnostic
                >
            ),
            InstanceMethod(
                "getFile",
                &TranslationUnit::dispatcher<
                    "getFile",
                    &TranslationUnit::getFile
                >
            ),
            InstanceMethod(
                "getSkippedRanges",
                &TranslationUnit::dispatcher<
                    "getSkippedRanges",
                    &TranslationUnit::getSkippedRanges
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
                "save",
                &TranslationUnit::dispatcher<
                    "save",
                    &TranslationUnit::save
                >
            ),
            InstanceMethod(
                "suspend",
                &TranslationUnit::dispatcher<
                    "suspend",
                    &TranslationUnit::suspend
                >
            ),
            StaticMethod(
                "defaultEditingOptions",
                &TranslationUnit::dispatcherStatic<
                    "defaultEditingOptions",
                    &TranslationUnit::defaultEditingOptions
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &TranslationUnit::dispatcher<"nodejs inspect", &TranslationUnit::nodejsInspect>),
        });
    Instance::get(env).translationUnitConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<TranslationUnit::State*, Napi::Object> TranslationUnit::construct(Napi::Env env)
{
    auto obj = Instance::get(env).translationUnitConstructor.New({});
    auto state = Napi::ObjectWrap<TranslationUnit>::Unwrap(obj)->state;
    return { state.get(), obj };
}

Napi::Function Type::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CType",
        {
            InstanceAccessor(
                "addressSpace",
                &Type::dispatcher<"get addressSpace", &Type::getAddressSpace>,
                nullptr
            ),
            InstanceAccessor(
                "canonicalType",
                &Type::dispatcher<"get canonicalType", &Type::canonicalType>,
                nullptr
            ),
            InstanceAccessor(
                "exceptionSpecificationType",
                &Type::dispatcher<"get exceptionSpecificationType", &Type::getExceptionSpecificationType>,
                nullptr
            ),
            InstanceAccessor(
                "functionTypeCallingConv",
                &Type::dispatcher<"get functionTypeCallingConv", &Type::getFunctionTypeCallingConv>,
                nullptr
            ),
            InstanceAccessor(
                "isConstQualifiedType",
                &Type::dispatcher<"get isConstQualifiedType", &Type::isConstQualifiedType>,
                nullptr
            ),
            InstanceAccessor(
                "isRestrictQualifiedType",
                &Type::dispatcher<"get isRestrictQualifiedType", &Type::isRestrictQualifiedType>,
                nullptr
            ),
            InstanceAccessor(
                "isVolatileQualifiedType",
                &Type::dispatcher<"get isVolatileQualifiedType", &Type::isVolatileQualifiedType>,
                nullptr
            ),
            InstanceAccessor(
                "kind",
                &Type::dispatcher<"get kind", &Type::getKind>,
                nullptr
            ),
            InstanceAccessor(
                "kindSpelling",
                &Type::dispatcher<"get kindSpelling", &Type::getKindSpellingImpl>,
                nullptr
            ),
            InstanceAccessor(
                "nonReferenceType",
                &Type::dispatcher<"get nonReferenceType", &Type::getNonReferenceType>,
                nullptr
            ),
            InstanceAccessor(
                "ObjCEncoding",
                &Type::dispatcher<"get ObjCEncoding", &Type::getObjCEncoding>,
                nullptr
            ),
            InstanceAccessor(
                "pointeeType",
                &Type::dispatcher<"get pointeeType", &Type::getPointeeType>,
                nullptr
            ),
            InstanceAccessor(
                "resultType",
                &Type::dispatcher<"get resultType", &Type::getResultType>,
                nullptr
            ),
            InstanceAccessor(
                "spelling",
                &Type::dispatcher<"get spelling", &Type::getSpelling>,
                nullptr
            ),
            InstanceAccessor(
                "typeDeclaration",
                &Type::dispatcher<"get typeDeclaration", &Type::getTypeDeclaration>,
                nullptr
            ),
            InstanceAccessor(
                "typedefName",
                &Type::dispatcher<"get typedefName", &Type::getTypedefName>,
                nullptr
            ),
            InstanceAccessor(
                "unqualifiedType",
                &Type::dispatcher<"get unqualifiedType", &Type::getUnqualifiedType>,
                nullptr
            ),
            InstanceMethod(
                "isEqual",
                &Type::dispatcher<
                    "isEqual",
                    &Type::isEqual
                >
            ),
            StaticMethod(
                "getKindSpelling",
                &Type::dispatcherStatic<
                    "getKindSpelling",
                    &Type::getKindSpelling
                >
            ),
            InstanceMethod(
                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),
                &Type::dispatcher<"nodejs inspect", &Type::nodejsInspect>),
        });
    Instance::get(env).typeConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<Type::State*, Napi::Object> Type::construct(Napi::Env env)
{
    auto obj = Instance::get(env).typeConstructor.New({});
    auto state = Napi::ObjectWrap<Type>::Unwrap(obj)->state;
    return { state.get(), obj };
}

Napi::Function VirtualFileOverlay::Init(Napi::Env env)
{
    Napi::Function func = DefineClass(
        env,
        "CVirtualFileOverlay",
        {
            InstanceAccessor(
                "caseSensitivity",
                nullptr,
                &VirtualFileOverlay::dispatcherSetter<"set caseSensitivity", &VirtualFileOverlay::setCaseSensitivity>
            ),
            InstanceMethod(
                "addFileMapping",
                &VirtualFileOverlay::dispatcher<
                    "addFileMapping",
                    &VirtualFileOverlay::addFileMapping
                >
            ),
            InstanceMethod(
                "writeToBuffer",
                &VirtualFileOverlay::dispatcher<
                    "writeToBuffer",
                    &VirtualFileOverlay::writeToBuffer
                >
            ),
            StaticMethod(
                "create",
                &VirtualFileOverlay::dispatcherStatic<
                    "create",
                    &VirtualFileOverlay::create
                >
            ),
        });
    Instance::get(env).virtualFileOverlayConstructor = Napi::Persistent(func);
    return func;
}

std::tuple<VirtualFileOverlay::State*, Napi::Object> VirtualFileOverlay::construct(Napi::Env env)
{
    auto obj = Instance::get(env).virtualFileOverlayConstructor.New({});
    auto state = Napi::ObjectWrap<VirtualFileOverlay>::Unwrap(obj)->state;
    return { state.get(), obj };
}
