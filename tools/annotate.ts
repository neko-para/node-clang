import { writeFileSync } from 'fs'
import path from 'path'

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

type ClassInfo = {
    name: string
    header: string
    methods: Record<string, string[]>
    staticMethods: Record<string, string[]>
    props: Record<
        string,
        {
            setter?: string
            getter?: string
        }
    >
    inspect?: string
}

function parseAnnotate(tu: CTranslationUnit) {
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
    const infos: ClassInfo[] = []
    for (const struct of structs) {
        const info: ClassInfo = {
            name: struct.spelling,
            header: path
                .relative(
                    path.join(process.cwd(), 'src'),
                    struct.location.expansionLocation[0].fileName
                )
                .replaceAll('\\', '/'),
            methods: {},
            staticMethods: {},
            props: {}
        }
        for (const method of directChild(struct).filter(x => x.kind === CXCursorKind.CXXMethod)) {
            const annotate = directChild(method, 1)[0]
            if (annotate?.kind !== CXCursorKind.AnnotateAttr) {
                continue
            }
            let type = annotate.spelling
            let target: string | null = null
            {
                const res = type.split(':')
                if (res.length === 2) {
                    type = res[0]
                    target = res[1]
                }
            }
            switch (type) {
                case 'method': {
                    const name = target ?? method.spelling
                    if (method.CXXMethod_isStatic) {
                        info.staticMethods[name] = info.staticMethods[name] ?? []
                        info.staticMethods[name].push(method.spelling)
                    } else {
                        info.methods[name] = info.methods[name] ?? []
                        info.methods[name].push(method.spelling)
                    }
                    break
                }
                case 'getter': {
                    let prop = method.spelling
                    if (prop.startsWith('get')) {
                        prop = prop[3].toLowerCase() + prop.substring(4)
                    }
                    if (target) {
                        prop = target
                    }
                    info.props[prop] = info.props[prop] ?? {}
                    info.props[prop].getter = method.spelling
                    break
                }
                case 'setter': {
                    let prop = method.spelling
                    if (prop.startsWith('set')) {
                        prop = prop[3].toLowerCase() + prop.substring(4)
                    }
                    if (target) {
                        prop = target
                    }
                    info.props[prop] = info.props[prop] ?? {}
                    info.props[prop].setter = method.spelling
                    break
                }
                case 'inspect':
                    info.inspect = method.spelling
                    break
            }
        }
        infos.push(info)
    }

    const cppSrc = ['#include <napi.h>', '']

    const headers = ['class/instance.h', ...new Set(infos.map(x => x.header))].sort((x, y) =>
        x.localeCompare(y)
    )
    cppSrc.push(...headers.map(hdr => `#include "${hdr}"`))

    infos.sort((x, y) => x.name.localeCompare(y.name))
    for (const info of infos) {
        cppSrc.push(
            '',
            `Napi::Function ${info.name}::Init(Napi::Env env)`,
            '{',
            '    Napi::Function func = DefineClass(',
            '        env,',
            `        "C${info.name}",`,
            '        {'
        )

        for (const [prop, func] of Object.entries(info.props).sort((x, y) =>
            x[0].localeCompare(y[0])
        )) {
            cppSrc.push(
                '            InstanceAccessor(',
                `                "${prop}",`,
                func.getter
                    ? `                &${info.name}::dispatcher<"get ${prop}", &${info.name}::${func.getter}>,`
                    : '                nullptr,',
                func.setter
                    ? `                &${info.name}::dispatcherSetter<"set ${prop}", &${info.name}::${func.setter}>`
                    : '                nullptr',
                '            ),'
            )
        }

        for (const [prop, funcs] of Object.entries(info.methods).sort((x, y) =>
            x[0].localeCompare(y[0])
        )) {
            cppSrc.push(
                '            InstanceMethod(',
                `                "${prop}",`,
                `                &${info.name}::dispatcher<`,
                `                    "${prop}",`,
                ...funcs.map(
                    (func, idx) =>
                        `                    &${info.name}::${func}${idx !== funcs.length - 1 ? ',' : ''}`
                ),
                '                >',
                '            ),'
            )
        }

        for (const [prop, funcs] of Object.entries(info.staticMethods).sort((x, y) =>
            x[0].localeCompare(y[0])
        )) {
            cppSrc.push(
                '            StaticMethod(',
                `                "${prop}",`,
                `                &${info.name}::dispatcherStatic<`,
                `                    "${prop}",`,
                ...funcs.map(
                    (func, idx) =>
                        `                    &${info.name}::${func}${idx !== funcs.length - 1 ? ',' : ''}`
                ),
                '                >',
                '            ),'
            )
        }

        if (info.inspect) {
            cppSrc.push(
                '            InstanceMethod(',
                '                Napi::Symbol::For(env, "nodejs.util.inspect.custom"),',
                `                &${info.name}::dispatcher<"nodejs inspect", &${info.name}::${info.inspect}>),`
            )
        }

        cppSrc.push(
            '        });',
            `    Instance::get(env).${info.name[0].toLowerCase() + info.name.substring(1)}Constructor = Napi::Persistent(func);`,
            '    return func;',
            '}'
        )
    }

    cppSrc.push('')

    writeFileSync('src/class/register.cpp', cppSrc.join('\n'))
}

function main() {
    const [index, tu] = load()

    parseAnnotate(tu)
}

main()
