import type { ulong, unsigned } from './base'
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
    set Size(value: unsigned): void
    get ThreadBackgroundPriorityForIndexing(): boolean
    set ThreadBackgroundPriorityForIndexing(value: boolean): void
    get ThreadBackgroundPriorityForEditing(): boolean
    set ThreadBackgroundPriorityForEditing(value: boolean): void
    get ExcludeDeclarationsFromPCH(): boolean
    set ExcludeDeclarationsFromPCH(value: boolean): void
    get DisplayDiagnostics(): boolean
    set DisplayDiagnostics(value: boolean): void
    get StorePreamblesInMemory(): boolean
    set StorePreamblesInMemory(value: boolean): void
    get PreambleStoragePath(): string | null
    set PreambleStoragePath(value: string | null): void
    get InvocationEmissionPath(): string | null
    set InvocationEmissionPath(value: string | null): void
}

export class CTranslationUnit {
    get spelling(): string
    reparse(unsaved_files: CUnsavedFile[], options: unsigned): CXErrorCode
    get cursor(): CCursor
}

export class CCursor {
    equal(cursor: CCursor): boolean
    get isNull(): boolean
    get hash(): unsigned
    get kind(): CXCursorKind
    get spelling(): string
    get translateUnit(): CTranslateUnit
    get type(): CType
    visitChildren(visitor: (cursor: CCursor, parent: CCursor) => CXChildVisitResult): boolean
}

export class CType {
    equal(type: CType): boolean
    get kind(): CXTypeKind
    get spelling(): string
}
