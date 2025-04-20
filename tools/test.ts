import { CCursor, CIndex, CTranslationUnit, CXChildVisitResult, CXCursorKind } from '../loader'
import { directChild, setup, visit } from './utils'

const includes = setup()

function load(): [CIndex, CTranslationUnit] {
    const index = new CIndex()
    index.create(false, true)
    const [tu, err] = index.parseTranslationUnit(
        'test.cpp',
        ['-xc++', '-std=c++20'].concat(includes.map(x => `-I${x}`)),
        [],
        0
    )
    if (!tu) {
        process.exit(0)
    }
    return [index, tu]
}

function test(tu: CTranslationUnit) {
    visit(tu.cursor, (cursor, parent, path) => {
        return CXChildVisitResult.Recurse
    })
}

function main() {
    const [index, tu] = load()

    test(tu)
}

main()
