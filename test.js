const { CCursor, CIndex, load, CIndexOptions } = require('./loader')

if (process.platform === 'win32') {
    load('C:/Program Files/LLVM/bin/libclang.dll')
} else {
    load('/usr/local/Cellar/llvm/20.1.1/lib/libclang.dylib')
}

const opt = new CIndexOptions()
console.log(opt)
for (const key in opt) {
    console.log(key, opt[key])
}
const index = new CIndex()
index.create(false, true)
// index.create(opt)
console.log(index)
