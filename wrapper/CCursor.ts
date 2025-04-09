import { Type } from './CType'
import { clang } from './native'

export class Cursor {
    __cursor: clang.CXCursor

    constructor(cursor: clang.CXCursor) {
        this.__cursor = cursor
    }

    equal(cursor: Cursor) {
        return clang.equalCursors(this.__cursor, cursor.__cursor)
    }

    get type() {
        return new Type(clang.getCursorType(this.__cursor))
    }

    get enumConstantDeclValue() {
        return clang.getEnumConstantDeclValue(this.__cursor)
    }

    get spelling() {
        return clang.getCursorSpelling(this.__cursor)
    }

    get kind() {
        return clang.getCursorKind(this.__cursor)
    }

    visitChildren(func: (cursor: Cursor, parent: Cursor) => clang.CXChildVisitResult) {
        return clang.visitChildren(this.__cursor, (cursor, parent) =>
            func(new Cursor(cursor), new Cursor(parent))
        )
    }
}
