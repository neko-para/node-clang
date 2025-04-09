import { writeFileSync } from 'fs'

import { Cursor, Index, TranslationUnit, clang } from '../wrapper'

if (process.platform === 'darwin') {
    clang.load('/usr/local/Cellar/llvm/20.1.1/lib/libclang.dylib')
}

function load(): [Index, TranslationUnit] {
    const index = Index.createIndex(false, true)!
    const tu = index.parseTranslationUnit(
        'third_party/clang-c/Index.h',
        [
            '-xc++',
            '-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include',
            '-I/Library/Developer/CommandLineTools/SDKs/MacOSX14.5.sdk/usr/include/c++/v1',
            '-Ithird_party'
        ],
        [],
        0
    )
    if (!tu) {
        process.exit(0)
    }
    return [index, tu]
}

function generateEnum(tu: TranslationUnit) {
    const findPrefix = (strs: string[]) => {
        let curr = strs[0]
        for (const next of strs.slice(1)) {
            while (!next.startsWith(curr)) {
                curr = curr.substring(0, curr.length - 1)
            }
        }
        return curr
    }

    const enums: Record<string, [string, bigint][]> = {}
    let enumKeys: [string, bigint][] = []

    const root = tu.cursor
    const cursors: Cursor[] = [root]
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
                enumKeys.push([cursor.spelling, cursor.enumConstantDeclValue])
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
        dtsSrc.push('}', '')
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
