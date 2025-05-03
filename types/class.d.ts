import type { int, longlong, ulong, ulonglong, unsigned } from './base'
import type {
    CXAvailabilityKind,
    CXCallingConv,
    CXChildVisitResult,
    CXCursorKind,
    CXCursor_ExceptionSpecificationKind,
    CXDiagnosticSeverity,
    CXErrorCode,
    CXLanguageKind,
    CXLinkageKind,
    CXLoadDiag_Error,
    CXSaveError,
    CXTLSKind,
    CXTUResourceUsageKind,
    CXTemplateArgumentKind,
    CXTypeKind,
    CXVisibilityKind
} from './enum'

export type CUnsavedFile = [filename: string, contents: string, length: ulong]
export type CVersion = [major: int, minor: int, subminor: int]
export type CPlatformAvailability = [
    platform: 'ios' | 'macos',
    introduced: CVersion,
    deprecated: CVersion,
    obsoleted: CVersion,
    unavailable: boolean,
    message: string
]

export class CGlobal {
    static buildSessionTimestamp(): ulonglong
}

export class CIndex {
    static create(
        exclude_declarations_from_pch: boolean,
        display_diagnostics: boolean
    ): CIndex | null
    static create(options: CIndexOptions): CIndex | null
    get globalOptions(): unsigned
    createTranslationUnitFromSourceFile(
        source_filename: string,
        clang_command_line_args: string[],
        unsaved_files: CUnsavedFile[]
    ): CTranslationUnit | null
    createTranslationUnit(ast_filename: string): [CTranslationUnit, null] | [null, CXErrorCode]
    parseTranslationUnit(
        source_filename: string,
        command_line_args: string[],
        unsaved_files: CUnsavedFile[],
        options: unsigned
    ): [CTranslationUnit, null] | [null, CXErrorCode]
    parseTranslationUnitFullArgv(
        source_filename: string,
        command_line_args: string[],
        unsaved_files: CUnsavedFile[],
        options: unsigned
    ): [CTranslationUnit, null] | [null, CXErrorCode]
}

export class CIndexOptions {
    get Size(): unsigned
    set Size(value: unsigned)
    get ThreadBackgroundPriorityForIndexing(): boolean
    set ThreadBackgroundPriorityForIndexing(value: boolean)
    get ThreadBackgroundPriorityForEditing(): boolean
    set ThreadBackgroundPriorityForEditing(value: boolean)
    get ExcludeDeclarationsFromPCH(): boolean
    set ExcludeDeclarationsFromPCH(value: boolean)
    get DisplayDiagnostics(): boolean
    set DisplayDiagnostics(value: boolean)
    get StorePreamblesInMemory(): boolean
    set StorePreamblesInMemory(value: boolean)
    get PreambleStoragePath(): string | null
    set PreambleStoragePath(value: string | null)
    get InvocationEmissionPath(): string | null
    set InvocationEmissionPath(value: string | null)
}

export class CTranslationUnit {
    getFile(file_name: string): CFile | null
    getSkippedRanges(file: CFile): CSourceRange[]
    get allSkippedRanges(): CSourceRange[]
    get numDiagnostics(): unsigned
    getDiagnostic(index: unsigned): CDiagnostic | null
    get diagnosticSet(): CDiagnosticSet | null
    get spelling(): string
    static defaultEditingOptions(): unsigned
    get defaultSaveOptions(): unsigned
    save(file_name: string, options: unsigned): CXSaveError
    suspend(): boolean
    get defaultReparseOptions(): unsigned
    reparse(unsaved_files: CUnsavedFile[], options: unsigned): CXErrorCode
    get resourceUsage(): [kind: CXTUResourceUsageKind, name: string, amount: ulong][]
    get targetInfo(): [triple: string | null, pointer_width: int | null]
    get cursor(): CCursor
    getCursor(location: CSourceLocation): CCursor
}

export class CCursor {
    static null(): CCursor
    isEqual(cursor: CCursor): boolean
    isEqual(cursor: CCursor, relax: boolean): boolean
    get isNull(): boolean
    get hash(): unsigned
    get kind(): CXCursorKind
    get kindStr(): string
    static isDeclaration(kind: CXCursorKind): boolean
    get isInvalidDeclaration(): boolean
    static isReference(kind: CXCursorKind): boolean
    static isExpression(kind: CXCursorKind): boolean
    static isStatement(kind: CXCursorKind): boolean
    static isAttribute(kind: CXCursorKind): boolean
    get hasAttrs(): boolean
    static isInvalid(kind: CXCursorKind): boolean
    static isTranslationUnit(kind: CXCursorKind): boolean
    static isPreprocessing(kind: CXCursorKind): boolean
    static isUnexposed(kind: CXCursorKind): boolean
    get linkage(): CXLinkageKind
    get visibility(): CXVisibilityKind
    get availability(): CXAvailabilityKind
    get platformAvailability(): [
        always_deprecated: boolean,
        deprecated_message: string,
        always_unavailable: boolean,
        unavailable_message: string,
        availability: CPlatformAvailability[]
    ]
    get varDeclInitializer(): CCursor
    get hasVarDeclGlobalStorage(): 1 | 0 | -1
    get hasVarDeclExternalStorage(): 1 | 0 | -1
    get language(): CXLanguageKind
    get TLSKind(): CXTLSKind
    get translationUnit(): CTranslationUnit | null
    get lexicalParent(): CCursor
    get semanticParent(): CCursor
    get overriddenCursors(): CCursor[] | null
    get includedFile(): CFile | null
    get location(): CSourceLocation
    get extent(): CSourceRange
    get type(): CType
    get typedefDeclUnderlyingType(): CType
    get enumDeclIntegerType(): CType
    get enumConstantDeclValue(): longlong
    get enumConstantDeclUnsignedValue(): ulonglong
    get isBitField(): boolean
    get fieldDeclBitWidth(): int
    get numArguments(): int
    getArgument(index: unsigned): CCursor
    get numTemplateArguments(): int
    getTemplateArgumentKind(index: unsigned): CXTemplateArgumentKind
    getTemplateArgumentType(index: unsigned): CType
    getTemplateArgumentValue(index: unsigned): longlong
    getTemplateArgumentUnsignedValue(index: unsigned): ulonglong
    get isMacroFunctionLike(): boolean
    get isMacroBuiltin(): boolean
    get isFunctionInlined(): boolean
    get declObjCTypeEncoding(): string

    get spelling(): string
    visitChildren(visitor: (cursor: CCursor, parent: CCursor) => CXChildVisitResult): boolean
    get mangling(): string
    get CXXManglings(): string[]
    get ObjCManglings(): string[]
    get CXXMethod_isStatic(): boolean

    __dump(): string
}

export class CCursorSet {
    static create(): CCursorSet
    contains(cursor: CCursor): boolean
    insert(cursor: CCursor): boolean
}

export class CType {
    isEqual(type: CType): boolean
    get kind(): CXTypeKind
    get kindSpelling(): string
    get spelling(): string
    get canonicalType(): CType
    get isConstQualifiedType(): boolean
    get isVolatileQualifiedType(): boolean
    get isRestrictQualifiedType(): boolean
    get addressSpace(): unsigned
    get typedefName(): string
    get pointeeType(): CType
    get unqualifiedType(): CType
    get nonReferenceType(): CType
    get typeDeclaration(): CCursor
    get ObjCEncoding(): string
    static getKindSpelling(kind: CXTypeKind): string
    get functionTypeCallingConv(): CXCallingConv
    get resultType(): CType
    get exceptionSpecificationType(): CXCursor_ExceptionSpecificationKind | -1
    get numArgTypes(): int | null
    getArgType(index: unsigned): CType
    get ObjCObjectBaseType(): CType
    get numObjCProtocolRefs(): unsigned
    getObjCProtocolDecl(index: unsigned): CCursor
    get numObjCTypeArgs(): unsigned
    getObjCTypeArg(index: unsigned): CType
}

export class CFile {
    get fileName(): string
    get fileTime(): Date
    get fileUniqueID(): [ulonglong, ulonglong, ulonglong] | null
    equal(file: CFile): boolean
    get realPathName(): string
    isMultipleIncludeGuarded(tu: CTranslationUnit): boolean
    getFileContents(tu: CTranslationUnit): string | null
    getLocation(tu: CTranslationUnit, line: unsigned, column: unsigned): CSourceLocation
    getLocation(tu: CTranslationUnit, offset: unsigned): CSourceLocation
}

export class CVirtualFileOverlay {
    static create(): CVirtualFileOverlay | null
    addFileMapping(virtualPath: string, realPath: string): CXErrorCode
    set caseSensitivity(value: boolean) // throw CXErrorCode
    writeToBuffer(): [ArrayBuffer, null] | [null, CXErrorCode]
}

export class CModuleMapDescriptor {
    static create(): CModuleMapDescriptor | null
    set frameworkModuleName(value: string) // throw CXErrorCode
    set umbrellaHeader(value: string) // throw CXErrorCode
    writeToBuffer(): [ArrayBuffer, null] | [null, CXErrorCode]
}

export class CSourceLocation {
    static null(): CSourceLocation
    isEqual(loc: CSourceLocation): boolean
    isBefore(loc: CSourceLocation): boolean
    get isInSystemHeader(): boolean
    get isFromMainFile(): boolean
    get expansionLocation(): [
        file: CFile | null,
        line: unsigned,
        column: unsigned,
        offset: unsigned
    ]
    get presumedLocation(): [filename: string, line: unsigned, column: unsigned]
    get spellingLocation(): [file: CFile | null, line: unsigned, column: unsigned, offset: unsigned]
    get fileLocation(): [file: CFile | null, line: unsigned, column: unsigned, offset: unsigned]
}

export class CSourceRange {
    static null(): CSourceRange
    static create(begin: CSourceLocation, end: CSourceLocation): CSourceRange
    isEqual(rng: CSourceRange): boolean
    get isNull(): boolean
    get start(): CSourceLocation
    get end(): CSourceLocation
}

export class CDiagnostic {
    get childDiagnostics(): CDiagnosticSet | null

    format(option: unsigned): string // CXDiagnosticDisplayOptions
    get severity(): CXDiagnosticSeverity
    get location(): CSourceLocation
    get spelling(): string
    get option(): [enable: string, disable: string]
    get category(): unsigned
    get categoryText(): string
    get numRanges(): unsigned
    getRange(index: unsigned): CSourceRange
    get numFixIts(): unsigned
    getFixIt(index: unsigned): [text: string, range: CSourceRange]
}

export class CDiagnosticSet {
    get length(): number
    getDiagnostic(index: unsigned): CDiagnostic | null
    static load(
        file: string
    ): [CDiagnosticSet, null] | [null, [error: CXLoadDiag_Error, error_string: string]]
}
