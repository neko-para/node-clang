import { writeFileSync } from 'fs'

import { CCursor, CIndex, CTranslationUnit, clang } from '../wrapper'

let includes: string[] = []
if (process.platform === 'darwin') {
    clang.load('/usr/local/Cellar/llvm/20.1.1/lib/libclang.dylib')
    includes = [
        '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include',
        '/Library/Developer/CommandLineTools/SDKs/MacOSX14.5.sdk/usr/include/c++/v1'
    ]
} else if (process.platform === 'win32') {
    clang.load('C:/Program Files/LLVM/bin/libclang.dll')
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

function load(): [CIndex, CTranslationUnit] {
    const index = CIndex.createIndex(false, true)!
    const tu = index.parseTranslationUnit(
        'third_party/clang-c/Index.h',
        ['-xc++', `-I${process.cwd()}/third_party`].concat(includes.map(x => `-I${x}`)),
        [],
        0
    )
    if (!tu) {
        process.exit(0)
    }
    return [index, tu]
}

function generateEnum(tu: CTranslationUnit) {
    const findPrefix = (strs: string[]) => {
        let curr = strs[0]
        for (const next of strs.slice(1)) {
            while (!next.startsWith(curr)) {
                curr = curr.substring(0, curr.length - 1)
            }
        }
        return curr
    }

    const enums: Record<string, [string, number][]> = {}
    let enumKeys: [string, number][] = []

    const root = tu.cursor
    const cursors: CCursor[] = [root]
    root.visitChildren((cursor, parent) => {
        while (!cursors[0].equal(parent)) {
            cursors.shift()
        }
        cursors.unshift(cursor)
        if (cursors.length === 2) {
            if (cursor.kind === clang.CXCursorKind.EnumDecl) {
                if (cursor.spelling.startsWith('CX')) {
                    enums[cursor.spelling] = []
                    enumKeys = enums[cursor.spelling]
                    return clang.CXChildVisitResult.Recurse
                } else {
                    return clang.CXChildVisitResult.Continue
                }
            } else {
                return clang.CXChildVisitResult.Continue
            }
        } else if (cursors.length === 3) {
            if (cursor.kind === clang.CXCursorKind.EnumConstantDecl) {
                const value = cursor.enumConstantDeclValue
                if (typeof value === 'bigint') {
                    console.error('Bigint enum not supported:', cursor.spelling, value)
                } else {
                    enumKeys.push([cursor.spelling, value])
                }
            }
            return clang.CXChildVisitResult.Continue
        } else {
            return clang.CXChildVisitResult.Break
        }
    })

    const cppSrc: string[] = [
        '#include "enum.h"',
        '',
        '#include <clang-c/Index.h>',
        '',
        'void implEnum(Napi::Object exports)',
        '{'
    ]

    const dtsSrc: string[] = []

    for (const [key, vals] of Object.entries(enums)) {
        const valKeys = vals.map(([k, _]) => k)
        const prefix = findPrefix(valKeys.length === 1 ? [key, ...valKeys] : valKeys)
        cppSrc.push(`    // ${key}`, `    auto ${key}_obj = Napi::Object::New(exports.Env());`)
        dtsSrc.push(`export const enum ${key} {`)
        for (const [val, num] of vals) {
            cppSrc.push(
                `    ${key}_obj["${val.replace(prefix, '')}"] = static_cast<int>(${val});`,
                `    static_assert(static_cast<int>(${val}) == ${num});`
            )
            dtsSrc.push(`    ${val.replace(prefix, '')} = ${num},`)
        }
        cppSrc.push(`    exports["${key}"] = ${key}_obj;`)
        dtsSrc.push('}')

        if (key === 'CXCursorKind' || key === 'CXTypeKind') {
            const backward: Record<number, string[]> = {}
            for (const [val, num] of vals) {
                const name = val.replace(prefix, '')
                if (name.startsWith('First') || name.startsWith('Last')) {
                    continue
                }
                backward[num] = backward[num] ?? []
                backward[num].push(name)
            }
            cppSrc.push(`    auto ${key}_strObj = Napi::Object::New(exports.Env());`)
            for (const [num, vals] of Object.entries(backward)) {
                cppSrc.push(`    ${key}_strObj["${num}"] = "${vals.join('/')}";`)
            }
            cppSrc.push(`    exports["${key}_str"] = ${key}_strObj;`)
            dtsSrc.push(`export declare const ${key}_str: Record<${key}, string>`)
        }

        dtsSrc.push('')
    }

    cppSrc.push('}', '')

    writeFileSync('src/api/enum.cpp', cppSrc.join('\n'))
    writeFileSync('types/enum.d.ts', dtsSrc.join('\n'))
}

function main() {
    const [index, tu] = load()
    generateEnum(tu)
}

main()
