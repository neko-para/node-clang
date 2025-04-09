import { Cursor } from './CCursor'
import { clang } from './native'

export class TranslationUnit {
    __tu: clang.CXTranslationUnit

    constructor(tu: clang.CXTranslationUnit) {
        this.__tu = tu
    }

    get cursor() {
        return new Cursor(clang.getTranslationUnitCursor(this.__tu))
    }
}
