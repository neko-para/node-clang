import { CCursor, CIndex, CTranslationUnit, CXChildVisitResult, CXCursorKind } from '../loader'
import { directChild, setup, visit } from './utils'

const includes = setup()

function load(): [CIndex, CTranslationUnit] {
    const index = new CIndex()
    index.create(false, true)
    const [tu, err] = index.parseTranslationUnit(
        'src/class/classes.h',
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
    let structs: CCursor[] = []
    visit(tu.cursor, (cursor, parent, path) => {
        if (cursor.location.isInSystemHeader) {
            return CXChildVisitResult.Continue
        }
        if (cursor.kind === CXCursorKind.StructDecl) {
            const child = directChild(cursor, 1)
            if (child[0]?.kind === CXCursorKind.AnnotateAttr) {
                structs.push(cursor)
            }
            return CXChildVisitResult.Continue
        }
        return CXChildVisitResult.Recurse
    })
    for (const struct of structs) {
        console.log(struct.spelling)
        for (const method of directChild(struct).filter(x => x.kind === CXCursorKind.CXXMethod)) {
            const annotate = directChild(method, 1)[0]
            if (annotate?.kind !== CXCursorKind.AnnotateAttr) {
                continue
            }
            console.log(method.CXXMethod_isStatic ? '+' : '-', method.spelling, annotate.spelling)
        }
    }
}

function main() {
    const [index, tu] = load()

    parseAnnotate(tu)
}

main()
