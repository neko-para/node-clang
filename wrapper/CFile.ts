import { clang } from './native'

export class CFile {
    __file: clang.CXFile

    constructor(file: clang.CXFile) {
        this.__file = file
    }
}
