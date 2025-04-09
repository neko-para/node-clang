import { TranslationUnit } from './CTranslationUnit'
import { clang } from './native'

export class Index {
    __index: clang.CXIndex

    constructor(idx: clang.CXIndex) {
        this.__index = idx
    }

    static createIndex(excludeDeclarationsFromPCH: boolean, displayDiagnostics: boolean) {
        const idx = clang.createIndex(excludeDeclarationsFromPCH, displayDiagnostics)
        return idx ? new Index(idx) : null
    }

    static createIndexWithOption(option: clang.CXIndexOptions) {
        const idx = clang.createIndexWithOptions(option)
        return idx ? new Index(idx) : null
    }

    parseTranslationUnit(
        source_filename: string,
        command_line_args: string[],
        unsaved_files: clang.CXUnsavedFile[],
        options: clang.unsigned
    ) {
        const tu = clang.parseTranslationUnit(
            this.__index,
            source_filename,
            command_line_args,
            unsaved_files,
            options
        )
        return tu ? new TranslationUnit(tu) : null
    }
}
