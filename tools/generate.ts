import { writeFileSync } from 'fs'

import clang, { CCursor, CIndex, CTranslationUnit, CXChildVisitResult } from '../loader'

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
    const index = new CIndex()
    index.create(false, true)
    const [tu, err] = index.parseTranslationUnit(
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
        if (cursors.length < 3) {
            return CXChildVisitResult.Recurse
        }
        if (cursors.length === 3) {
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
        } else if (cursors.length === 4) {
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
            return clang.CXChildVisitResult.Continue
        }
    })

    const cppSrc: string[] = [
        '#include "enum.h"',
        '',
        '#include <clang-c/Index.h>',
        '',
        'std::map<CXCursorKind, std::string> cursorKind_enum2str = {};',
        'std::map<std::string, CXCursorKind> cursorKind_str2enum = {};',
        'std::map<CXTypeKind, std::string> typeKind_enum2str = {};',
        'std::map<std::string, CXTypeKind> typeKind_str2enum = {};',
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
            if (key === 'CXCursorKind') {
                cppSrc.push(`    cursorKind_str2enum["${val.replace(prefix, '')}"] = ${val};`)
                cppSrc.push(`    cursorKind_enum2str[${val}] = "${val.replace(prefix, '')}";`)
            } else if (key === 'CXTypeKind') {
                cppSrc.push(`    typeKind_str2enum["${val.replace(prefix, '')}"] = ${val};`)
                cppSrc.push(`    typeKind_enum2str[${val}] = "${val.replace(prefix, '')}";`)
            }
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

    writeFileSync('src/enum.cpp', cppSrc.join('\n'))
    writeFileSync('types/enum.d.ts', dtsSrc.join('\n'))
}

function generateFunc(tu: CTranslationUnit) {
    const cppSrc: string[] = [
        '#pragma once',
        '',
        '#include <clang-c/Index.h>',
        '',
        '#include "loader/loader.h"',
        '',
        'struct Library : public LibraryBase',
        '{'
    ]

    const funcs: string[] = []

    const deprecate = ['clang_getDiagnosticCategoryName']

    const root = tu.cursor
    const cursors: CCursor[] = [root]
    root.visitChildren((cursor, parent) => {
        while (!cursors[0].equal(parent)) {
            cursors.shift()
        }
        cursors.unshift(cursor)
        if (cursors.length < 3) {
            return clang.CXChildVisitResult.Recurse
        }

        if (cursors.length === 3 && cursor.kind === clang.CXCursorKind.FunctionDecl) {
            if (cursor.spelling.startsWith('clang_') && !deprecate.includes(cursor.spelling)) {
                funcs.push(cursor.spelling)
            }
        }
        return clang.CXChildVisitResult.Continue
    })

    for (const func of funcs) {
        cppSrc.push(`    decltype(${func})* ${func.replace('clang_', '')};`)
    }

    cppSrc.push('', '    Library(const char* path) : LibraryBase(path)', '    {')

    for (const func of funcs) {
        cppSrc.push(
            `        ${func.replace('clang_', '')} = lib_get_func<decltype(${func})*>(library_, "${func}");`
        )
    }

    cppSrc.push('    }', '};', '')

    writeFileSync('src/loader/clang.h', cppSrc.join('\n'))
}

function main() {
    const [index, tu] = load()
    generateEnum(tu)

    generateFunc(tu)
}

main()
