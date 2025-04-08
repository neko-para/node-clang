import clang from './types'

if (process.platform === 'darwin') {
    clang.load('/usr/local/Cellar/llvm/20.1.1/lib/libclang.dylib')
}

const index = clang.createIndex(false, true)
const tu = clang.parseTranslationUnit(
    index!,
    'src/lib.h',
    [
        '-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include',
        '-I/Library/Developer/CommandLineTools/SDKs/MacOSX14.5.sdk/usr/include/c++/v1',
        '-xc++'
    ],
    [],
    0
)
if (!tu) {
    process.exit(0)
}
const root = clang.getTranslationUnitCursor(tu)

const cursors: clang.CXCursor[] = [root]
clang.visitChildren(root, (cursor, parent) => {
    while (!clang.equalCursors(cursors[0], parent)) {
        cursors.shift()
    }
    cursors.unshift(cursor)
    console.log(
        '  '.repeat(cursors.length - 1) + clang.__CXCursorKind_NumStr[clang.getCursorKind(cursor)],
        clang.getCursorSpelling(cursor)
    )
    return 'recurse'
})
