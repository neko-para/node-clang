if (process.platform === 'win32') {
    module.exports = require('../build/Debug/NodeClang.node')
} else {
    module.exports = require('../build/NodeClang.node')
}
