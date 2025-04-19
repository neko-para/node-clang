const { CCursor, CIndex, load, CIndexOptions, CXChildVisitResult } = require('./loader')

if (process.platform === 'win32') {
    load('C:/Program Files/LLVM/bin/libclang.dll')
} else {
    load('/usr/local/Cellar/llvm/20.1.1/lib/libclang.dylib')
}

const opt = new CIndexOptions()
console.log(opt)
const index = new CIndex()
index.create(false, true)
console.log(index)

const [tu, err] = index.parseTranslationUnit('test.cpp', [], [], 0)
if (!tu) {
    process.exit(0)
}

const f = tu.getFile('test.cpp')
if (f) {
    console.log(f)
}

tu.cursor.visitChildren((cursor, parent) => {
    console.log(cursor, cursor.type)
    return CXChildVisitResult.Recurse
})
