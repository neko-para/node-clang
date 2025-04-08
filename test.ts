import clang from './types'

if (process.platform === 'darwin') {
    clang.load('/usr/local/Cellar/llvm/20.1.1/lib/libclang.dylib')
}

const index = clang.createIndex(0, 1)
const tu = clang.parseTranslationUnit(index!, 'src/lib.h', [], [], 0)
if (!tu) {
    process.exit(0)
}
const kind = clang.getTranslationUnitCursor(tu).kind

console.log(clang.__CXCursorKind_NumStr[kind], clang.__CXCursorKind_NumStr)
