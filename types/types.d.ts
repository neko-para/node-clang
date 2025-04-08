import type { int, uchar, unsigned } from './base'

export type CXIndex = { __brand: 'CXIndex' }
export type CXTargetInfo = { __brand: 'CXTargetInfo' }
export type CXTranslationUnit = { __brand: 'CXTranslationUnit' }
export type CXUnsavedFile = {
    Filename: string
    Contents: string
}
export const enum CXAvailabilityKind {
    Available,
    Deprecated,
    NotAvailable,
    NotAccessible
}
export type CXVersion = {
    major: int
    minor: int
    subminor: int
}
export const enum CXCursor_ExceptionSpecificationKind {
    None,
    DynamicNone,
    Dynamic,
    MSAny,
    BasicNoexcept,
    ComputedNoexcept,
    Unevaluated,
    Uninstantiated,
    Unparsed,
    NoThrow
}
export const enum CXChoice {
    Default = 0,
    Enabled = 1,
    Disabled = 2
}
export const enum CXGlobalOpt {
    None = 0x0,
    ThreadBackgroundPriorityForIndexing = 0x1,
    ThreadBackgroundPriorityForEditing = 0x2,
    ThreadBackgroundPriorityForAll = ThreadBackgroundPriorityForIndexing |
        ThreadBackgroundPriorityForEditing
}
export type CXGlobalOptFlags = unsigned
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

// CXFile.h

export type CXFile = { __brand: 'CXFile' }

// CXSourceLocation.h

export type CXSourceLocation = { __brand: 'CXSourceLocation' }
export type CXSourceRange = { __brand: 'CXSourceRange' }
