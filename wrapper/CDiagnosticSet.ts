import { CDiagnostic } from './CDiagnostic'
import { clang } from './native'

export class CDiagnosticSet {
    __diags: clang.CXDiagnosticSet

    constructor(diags: clang.CXDiagnosticSet) {
        this.__diags = diags
    }

    get numDiagnostics() {
        return clang.getNumDiagnosticsInSet(this.__diags)
    }

    getDiagnostic(index: clang.unsigned) {
        return new CDiagnostic(clang.getDiagnosticInSet(this.__diags, index))
    }

    static load(file: string) {
        return clang.loadDiagnostics(file)
    }
}
