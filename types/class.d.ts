import type { longlong, ulong, ulonglong, unsigned } from './base'
import type { CXChildVisitResult, CXCursorKind, CXErrorCode, CXTypeKind } from './enum'

export type CUnsavedFile = [Filename: string, Contents: string, Length: ulong]

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
    equal(cursor: CCursor): boolean
    get isNull(): boolean
    get hash(): unsigned
    get kind(): CXCursorKind
    get kindStr(): string
    get spelling(): string
    get translationUnit(): CTranslationUnit
    get type(): CType
    get location(): CSourceLocation
    get enumConstantDeclValue(): longlong
    visitChildren(visitor: (cursor: CCursor, parent: CCursor) => CXChildVisitResult): boolean
    get CXXMethod_isStatic(): boolean
}

export class CType {
    equal(type: CType): boolean
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
    get isInSystemHeader(): boolean
    get expansionLocation(): [file: CFile, line: unsigned, column: unsigned, offset: unsigned]
    get presumedLocation(): [filename: string, line: unsigned, column: unsigned]
}
