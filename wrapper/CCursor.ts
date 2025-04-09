import { CType } from './CType'
import { clang } from './native'

export class CCursor {
    __cursor: clang.CXCursor

    constructor(cursor: clang.CXCursor) {
        this.__cursor = cursor
    }

    equal(cursor: CCursor) {
        return clang.equalCursors(this.__cursor, cursor.__cursor)
    }

    get type() {
        return new CType(clang.getCursorType(this.__cursor))
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

    visitChildren(func: (cursor: CCursor, parent: CCursor) => clang.CXChildVisitResult) {
        return clang.visitChildren(this.__cursor, (cursor, parent) =>
            func(new CCursor(cursor), new CCursor(parent))
        )
    }
}
