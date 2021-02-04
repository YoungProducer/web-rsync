const fileChecksum = require('./build/Release/file-checksum.node');

console.log(fileChecksum.sha256_checksum('./output.txt'))