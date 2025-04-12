import { CDiagnosticSet } from './CDiagnosticSet'
import { clang } from './native'

export class CDiagnostic {
    __diag: clang.CXDiagnostic

    constructor(diag: clang.CXDiagnostic) {
        this.__diag = diag
    }

    get child() {
        return new CDiagnosticSet(clang.getChildDiagnostics(this.__diag))
    }

    format(options: clang.unsigned) {
        return clang.formatDiagnostic(this.__diag, options)
    }

    static defaultDisplayOptions() {
        return clang.defaultDiagnosticDisplayOptions()
    }
}
