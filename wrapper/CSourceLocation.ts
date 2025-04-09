import { clang } from './native'

export class CSourceLocation {
    __loc: clang.CXSourceLocation

    constructor(loc: clang.CXSourceLocation) {
        this.__loc = loc
    }
}
