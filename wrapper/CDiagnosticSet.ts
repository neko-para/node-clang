import { clang } from './native'

export class CDiagnosticSet {
    __diags: clang.CXDiagnosticSet

    constructor(diags: clang.CXDiagnosticSet) {
        this.__diags = diags
    }
}
