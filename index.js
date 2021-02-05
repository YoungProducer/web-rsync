const fileChecksum = require('./build/Release/file-checksum.node');

// console.log(fileChecksum.sha256_checksum('./test-files/image.png'))
fileChecksum.test('./dist/')