import type { unsigned } from './base'

export class CIndex {
    create(excludeDeclarationsFromPCH: boolean, displayDiagnostics: boolean): boolean
    get globalOptions(): unsigned
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

export class CCursor {
    constructor()
}
