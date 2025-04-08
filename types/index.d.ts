import type { CXCursorKind } from './CXCursorKind.d'
import type { unsigned } from './base.d'

export * from './CXCursorKind.d'
export * from './base.d'

export type CXIndex = { __brand: 'CXIndex' }
export type CXTranslationUnit = { __brand: 'CXTranslationUnit' }
export type CXUnsavedFile = { __brand: 'CXUnsavedFile' }
export type CXCursor = { __brand: 'CXCursor' }

export function load(path: string): boolean
export function loaded(): boolean

export function createIndex(
    excludeDeclarationsFromPCH: boolean,
    displayDiagnostics: boolean
): CXIndex | null
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
