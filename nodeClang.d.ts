type int = number
type unsigned = number

export const enum CXCursorKind {
  UnexposedDecl = 1,
}

export type CXIndex = { __brand: 'CXIndex' }
export type CXTranslationUnit = { __brand: 'CXTranslationUnit' }
export type CXUnsavedFile = null
export type CXCursor = { 
  kind: CXCursorKind
  __data: unknown
  __brand: 'CXCursor'
}

export function load(path: string): boolean
export function loaded(): boolean

export function createIndex(excludeDeclarationsFromPCH: int, displayDiagnostics: int): CXIndex | null
export function parseTranslationUnit(CIdx: CXIndex, source_filename: string, command_line_args: string[], unsaved_files: CXUnsavedFile[], options: unsigned): CXTranslationUnit | null
export function getTranslationUnitCursor(tu: CXTranslationUnit): CXCursor
