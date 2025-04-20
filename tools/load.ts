import { load } from '../loader'

export function setup() {
    let includes: string[] = []
    if (process.platform === 'darwin') {
        load('/usr/local/Cellar/llvm/20.1.1/lib/libclang.dylib')
        includes = [
            '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include',
            '/Library/Developer/CommandLineTools/SDKs/MacOSX14.5.sdk/usr/include/c++/v1'
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
