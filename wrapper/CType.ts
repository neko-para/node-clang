import { clang } from './native'

export class CType {
    __type: clang.CXType

    constructor(type: clang.CXType) {
        this.__type = type
    }

    get spelling() {
        return clang.getTypeSpelling(this.__type)
    }
}
