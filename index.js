const native = require('./build/Release/file-checksum.node');
const lib = require('./lib');

module.exports = { ...native, ...lib };
