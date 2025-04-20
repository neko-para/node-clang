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
    const root = tu.cursor
    let outter: CCursor | null = null
    let structName: string = ''
    let isTarget: boolean = false
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
    console.log(structs)
    /*
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
        */
}

function main() {
    const [index, tu] = load()

    parseAnnotate(tu)
}

main()
