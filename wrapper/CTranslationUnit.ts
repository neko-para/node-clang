import { CCursor } from './CCursor'
import { CDiagnostic } from './CDiagnostic'
import { CDiagnosticSet } from './CDiagnosticSet'
import { CFile } from './CFile'
import { CSourceLocation } from './CSourceLocation'
import { CSourceRange } from './CSourceRange'
import { clang } from './native'

export class CTranslationUnit {
    __tu: clang.CXTranslationUnit

    constructor(tu: clang.CXTranslationUnit) {
        this.__tu = tu
    }

    isFileMultipleIncludeGuarded(file: CFile) {
        return clang.isFileMultipleIncludeGuarded(this.__tu, file.__file)
    }

    getFile(file_name: string) {
        const file = clang.getFile(this.__tu, file_name)
        return file ? new CFile(file) : null
    }

    getFileContents(file: CFile) {
        return clang.getFileContents(this.__tu, file.__file)
    }

    getLocation(file: CFile, line: clang.unsigned, column: clang.unsigned) {
        return new CSourceLocation(clang.getLocation(this.__tu, file.__file, line, column))
    }

    getLocationForOffset(file: CFile, offset: clang.unsigned) {
        return new CSourceLocation(clang.getLocationForOffset(this.__tu, file.__file, offset))
    }

    getSkippedRanges(file: CFile) {
        const rngs = clang.getSkippedRanges(this.__tu, file.__file)
        return rngs !== null ? rngs.map(rng => new CSourceRange(rng)) : null
    }

    get allSkippedRanges() {
        const rngs = clang.getAllSkippedRanges(this.__tu)
        return rngs !== null ? rngs.map(rng => new CSourceRange(rng)) : null
    }

    get numDiagnostics() {
        return clang.getNumDiagnostics(this.__tu)
    }

    getDiagnostic(index: clang.unsigned) {
        const diag = clang.getDiagnostic(this.__tu, index)
        return diag ? new CDiagnostic(diag) : null
    }

    get diagnosticSet() {
        const diags = clang.getDiagnosticSetFromTU(this.__tu)
        return diags ? new CDiagnosticSet(diags) : null
    }

    get cursor() {
        return new CCursor(clang.getTranslationUnitCursor(this.__tu))
    }
}
