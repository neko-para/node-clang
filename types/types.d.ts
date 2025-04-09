import type { int, uchar, unsigned } from './base'

export type CXIndex = { __brand: 'CXIndex' }
export type CXTargetInfo = { __brand: 'CXTargetInfo' }
export type CXTranslationUnit = { __brand: 'CXTranslationUnit' }
export type CXUnsavedFile = {
    Filename: string
    Contents: string
}
export type CXVersion = {
    major: int
    minor: int
    subminor: int
}
export type CXIndexOptions = {
    Size: unsigned
    ThreadBackgroundPriorityForIndexing: uchar
    ThreadBackgroundPriorityForEditing: uchar
    ExcludeDeclarationsFromPCH: boolean
    DisplayDiagnostics: boolean
    StorePreamblesInMemory: boolean
    // reserved
    PreambleStoragePath: string
    InvocationEmissionPath: string
}

//

export type CXCursor = { __brand: 'CXCursor' }
export type CXType = { __brand: 'CXType' }

// CXFile.h

export type CXFile = { __brand: 'CXFile' }

// CXSourceLocation.h

export type CXSourceLocation = { __brand: 'CXSourceLocation' }
export type CXSourceRange = { __brand: 'CXSourceRange' }
