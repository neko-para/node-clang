import { clang } from './native'

export class CSourceRange {
    __rng: clang.CXSourceRange

    constructor(rng: clang.CXSourceRange) {
        this.__rng = rng
    }
}
