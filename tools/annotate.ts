import { CCursor, CIndex, CTranslationUnit, CXChildVisitResult, CXCursorKind } from '../loader'
import { setup } from './load'

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
    const root = tu.cursor
    let outter: CCursor | null = null
    let structName: string = ''
    let isTarget: boolean = false
    tu.cursor.visitChildren((cursor, parent) => {
        if (outter && outter.equal(parent)) {
            outter = null
            structName = ''
            isTarget = false
        }
        if (!structName) {
            if (cursor.kind === CXCursorKind.StructDecl) {
                outter = parent
                structName = cursor.spelling
                isTarget = false
                return CXChildVisitResult.Recurse
            } else {
                return CXChildVisitResult.Continue
            }
        } else if (!isTarget) {
            if (cursor.kind === CXCursorKind.AnnotateAttr && cursor.spelling === 'class') {
                isTarget = true
                console.log(structName)
            } else {
                structName = ''
            }
            return CXChildVisitResult.Continue
        } else {
            // console.log(cursor)
            if (cursor.kind === CXCursorKind.CXXMethod) {
                if (cursor.CXXMethod_isStatic) {
                    console.log('+', cursor.spelling)
                } else {
                    console.log('-', cursor.spelling)
                }
            }
            return CXChildVisitResult.Continue
        }
    })
}

function main() {
    const [index, tu] = load()

    parseAnnotate(tu)
}

main()
