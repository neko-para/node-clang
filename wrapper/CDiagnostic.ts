import { clang } from './native'

export class CDiagnostic {
    __diag: clang.CXDiagnostic

    constructor(diag: clang.CXDiagnostic) {
        this.__diag = diag
    }
}
