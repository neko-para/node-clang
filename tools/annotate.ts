import { CCursor, CIndex, CTranslationUnit, CXChildVisitResult, CXCursorKind } from '../loader'
import { setup } from './load'

const includes = setup()

function load(): [CIndex, CTranslationUnit] {
    const index = new CIndex()
    index.create(false, true)
    const [tu, err] = index.parseTranslationUnit(
        'test.cpp',
        [
            '-xc++',
            '-std=c++20',
            `-I${process.cwd()}/third_party`,
            `-I${process.cwd()}/src`,
            `-I${process.cwd()}/node_modules/node-api-headers/include`,
            `-I${process.cwd()}/node_modules/node-addon-api`
        ].concat(includes.map(x => `-I${x}`)),
        [],
        0
    )
    if (!tu) {
        process.exit(0)
    }
    return [index, tu]
}

function parseAnnotate(tu: CTranslationUnit) {
    const root = tu.cursor
    const cursors: CCursor[] = [root]
    tu.cursor.visitChildren((cursor, parent) => {
        if (cursor.spelling === '_Const_lvalue_cond_oper') {
            console.log(111)
        }
        while (cursors.length > 0 && !cursors[0].equal(parent)) {
            cursors.shift()
        }
        if (cursors.length === 0) {
            console.warn('jump out root', cursor, parent)
        }
        cursors.unshift(cursor)

        console.log('  '.repeat(cursors.length - 2), cursor.spelling, cursor.kindStr)
        return CXChildVisitResult.Recurse
    })
}

function main() {
    const [index, tu] = load()

    parseAnnotate(tu)
}

main()
