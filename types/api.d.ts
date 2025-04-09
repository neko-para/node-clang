import { unsigned } from './base'
import { CXChildVisitResult, CXCursorKind } from './enum'
import {
    CXCursor,
    CXFile,
    CXIndex,
    CXIndexOptions,
    CXSourceLocation,
    CXSourceRange,
    CXTranslationUnit,
    CXType,
    CXUnsavedFile
} from './types'

export function createIndex(
    excludeDeclarationsFromPCH: boolean,
    displayDiagnostics: boolean
): CXIndex | null
export function createIndexWithOptions(options: CXIndexOptions): CXIndex | null
// deprecated CXIndex_setGlobalOptions
export function CXIndex_getGlobalOptions(index: CXIndex): unsigned
// deprecated CXIndex_setInvocationEmissionPathOption
export function isFileMultipleIncludeGuarded(tu: CXTranslationUnit, file: CXFile): boolean
export function getFile(tu: CXTranslationUnit, file_name: string): CXFile | null
export function getFileContents(tu: CXTranslationUnit, file: CXFile): string | null
export function getLocation(
    tu: CXTranslationUnit,
    file: CXFile,
    line: unsigned,
    column: unsigned
): CXSourceLocation
export function getLocationForOffset(
    tu: CXTranslationUnit,
    file: CXFile,
    offset: unsigned
): CXSourceLocation
export function getSkippedRanges(tu: CXTranslationUnit, file: CXFile): CXSourceRange[] | null
export function getAllSkippedRanges(tu: CXTranslationUnit): CXSourceRange[] | null

//

export function equalCursors(cursorA: CXCursor, cursorB: CXCursor): boolean
export function getCursorType(C: CXCursor): CXType
export function getTypeSpelling(CT: CXType): string
export function getEnumConstantDeclValue(C: CXCursor): number | bigint
export function getCursorSpelling(cursor: CXCursor): string
export function getCursorKind(cursor: CXCursor): CXCursorKind

//

export function parseTranslationUnit(
    CIdx: CXIndex,
    source_filename: string,
    command_line_args: string[],
    unsaved_files: CXUnsavedFile[],
    options: unsigned
): CXTranslationUnit | null
export function getTranslationUnitCursor(tu: CXTranslationUnit): CXCursor
export function visitChildren(
    parent: CXCursor,
    visitor: (cursor: CXCursor, parent: CXCursor) => CXChildVisitResult
): boolean
