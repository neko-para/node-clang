import type { longlong, ulong, ulonglong, unsigned } from './base'
import type { CXChildVisitResult, CXCursorKind, CXErrorCode, CXTypeKind } from './enum'

export type CUnsavedFile = [Filename: string, Contents: string, Length: ulong]

export class CGlobal {
    static buildSessionTimestamp(): ulonglong
}

export class CIndex {
    create(excludeDeclarationsFromPCH: boolean, displayDiagnostics: boolean): boolean
    create(options: CIndexOptions): boolean
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
    get spelling(): string
    reparse(unsaved_files: CUnsavedFile[], options: unsigned): CXErrorCode
    get cursor(): CCursor
}

export class CCursor {
    static null(): CCursor
    isEqual(cursor: CCursor): boolean
    isEqual(cursor: CCursor, relax: boolean): boolean
    get isNull(): boolean
    get hash(): unsigned
    get kind(): CXCursorKind
    get kindStr(): string
    get spelling(): string
    get translationUnit(): CTranslationUnit | null
    get type(): CType
    get lexicalParent(): CCursor
    get semanticParent(): CCursor
    get location(): CSourceLocation
    get enumConstantDeclValue(): longlong
    visitChildren(visitor: (cursor: CCursor, parent: CCursor) => CXChildVisitResult): boolean
    get CXXMethod_isStatic(): boolean

    __dump(): string
}

export class CType {
    isEqual(type: CType): boolean
    get kind(): CXTypeKind
    get kindStr(): string
    get spelling(): string
}

export class CFile {
    get fileName(): string
    get fileTime(): Date
    get fileUniqueID(): [ulonglong, ulonglong, ulonglong] | null
    equal(file: CFile): boolean
    get realPathName(): string
    get isMultipleIncludeGuarded(): boolean
    get fileContents(): string | null
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
}

export class CVirtualFileOverlay {
    create(): boolean
    addFileMapping(virtualPath: string, realPath: string): CXErrorCode
    set caseSensitivity(value: boolean) // throw CXErrorCode
    writeToBuffer(): ArrayBuffer // throw CXErrorCode
}

export class CModuleMapDescriptor {
    create(): boolean
    set frameworkModuleName(value: string) // throw CXErrorCode
    set umbrellaHeader(value: string) // throw CXErrorCode
    writeToBuffer(): ArrayBuffer // throw CXErrorCode
}
