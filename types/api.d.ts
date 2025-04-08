import { CXCursorKind } from './CXCursorKind'
import { unsigned } from './base'
import {
    CXCursor,
    CXFile,
    CXGlobalOptFlags,
    CXIndex,
    CXIndexOptions,
    CXSourceLocation,
    CXTranslationUnit,
    CXUnsavedFile
} from './types'

export function createIndex(
    excludeDeclarationsFromPCH: boolean,
    displayDiagnostics: boolean
): CXIndex | null
export function createIndexWithOptions(options: CXIndexOptions): CXIndex | null
// deprecated CXIndex_setGlobalOptions
export function CXIndex_getGlobalOptions(index: CXIndex): CXGlobalOptFlags
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
    visitor: (cursor: CXCursor, parent: CXCursor) => 'break' | 'continue' | 'recurse'
): boolean
export function equalCursors(cursorA: CXCursor, cursorB: CXCursor): boolean
export function getCursorSpelling(cursor: CXCursor): string
export function getCursorKind(cursor: CXCursor): CXCursorKind
