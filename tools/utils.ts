import { CCursor, CXChildVisitResult, load } from '../loader'

export function setup() {
    let includes: string[] = []
    if (process.platform === 'darwin') {
        load('/usr/local/Cellar/llvm/20.1.1/lib/libclang.dylib')
        includes = [
            '/Library/Developer/CommandLineTools/SDKs/MacOSX14.5.sdk/usr/include/c++/v1',
            '/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/15.0.0/include',
            '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include',
            '/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include'
        ]
    } else if (process.platform === 'win32') {
        load('C:/Program Files/LLVM/bin/libclang.dll')
        includes = [
            'C:/Program Files/LLVM/lib/clang/20/include',
            'C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/include',
            'C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/atlmfc/include',
            'C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/ucrt',
            'C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/shared',
            'C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/um',
            'C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/winrt',
            'C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/cppwinrt'
        ]
    }
    return includes
}

export function visit(
    root: CCursor,
    visitor: (cursor: CCursor, parent: CCursor, path: CCursor[]) => CXChildVisitResult,
    discard = true
) {
    const stack = [root]
    return root.visitChildren((cursor, parent) => {
        let idx = stack.findIndex(x => x.equal(parent))
        if (idx === -1) {
            // https://github.com/llvm/llvm-project/issues/136435
            // equal may return incorrect result, retry relaxed one.
            idx = stack.findIndex(x => x.equal(parent, true))
            if (idx === -1) {
                let grandParent = parent.lexicalParent
                if (grandParent.isNull) {
                    grandParent = parent.semanticParent
                }
                if (!grandParent.isNull) {
                    let idx2 = stack.findIndex(x => x.equal(grandParent))
                    if (idx2 === -1) {
                        idx2 = stack.findIndex(x => x.equal(grandParent, true))
                    }
                    if (idx2 !== -1) {
                        stack.splice(idx2 + 1)
                        stack.push(parent)
                        visitor(parent, grandParent, stack) // ignore!
                        stack.push(cursor)
                        return visitor(cursor, parent, stack)
                    }
                }
                if (!discard) {
                    console.log(
                        cursor,
                        cursor.__dump(),
                        cursor.location.expansionLocation[0].fileName
                    )
                    console.log(
                        parent,
                        parent.__dump(),
                        parent.lexicalParent,
                        parent.semanticParent
                    )
                    console.log('')
                    for (const tr of stack.slice(stack.length - 5)) {
                        console.log(tr, tr.__dump())
                    }
                    throw '???'
                } else {
                    console.log('discard', cursor)
                    return CXChildVisitResult.Continue
                }
            }
        }
        stack.splice(idx + 1)
        stack.push(cursor)
        return visitor(cursor, parent, [...stack])
    })
}

export function directChild(root: CCursor, maxi?: number) {
    const child: CCursor[] = []
    root.visitChildren(cursor => {
        child.push(cursor)
        return typeof maxi === 'number' && child.length >= maxi
            ? CXChildVisitResult.Break
            : CXChildVisitResult.Continue
    })
    return child
}
