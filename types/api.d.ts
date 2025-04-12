import { unsigned } from './base'
import { CXChildVisitResult, CXCursorKind, CXLoadDiag_Error } from './enum'
import {
    CXCursor,
    CXDiagnostic,
    CXDiagnosticSet,
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
export function getNumDiagnostics(Unit: CXTranslationUnit): unsigned
export function getDiagnostic(Unit: CXTranslationUnit, Index: unsigned): CXDiagnostic | null
export function getDiagnosticSetFromTU(Unit: CXTranslationUnit): CXDiagnosticSet | null
//

export function equalCursors(cursorA: CXCursor, cursorB: CXCursor): boolean
export function getCursorType(C: CXCursor): CXType
export function getTypeSpelling(CT: CXType): string
export function getEnumConstantDeclValue(C: CXCursor): number | bigint
export function getCursorSpelling(cursor: CXCursor): string
export function getCursorKind(cursor: CXCursor): CXCursorKind

//

// CXDiagnostic.h

export function getNumDiagnosticsInSet(Diags: CXDiagnosticSet): number
export function getDiagnosticInSet(Diags: CXDiagnosticSet, Index: unsigned): CXDiagnostic
export function loadDiagnostics(
    file: string
): [result: CXDiagnosticSet, error: CXLoadDiag_Error, errorString: string] | null
export function getChildDiagnostics(D: CXDiagnostic): CXDiagnosticSet
/** @param Options: CXDiagnosticDisplayOptions */
export function formatDiagnostic(Diagnostic: CXDiagnostic, Options: unsigned): string
/** @returns CXDiagnosticDisplayOptions */
export function defaultDiagnosticDisplayOptions(): unsigned

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
