import { CCursor, CIndex, load } from './loader'

load('C:/Program Files/LLVM/bin/libclang.dll')

const index = new CIndex(false, true)
// const index1 = new CIndex(false)
const index2 = new CIndex(false, 1)
