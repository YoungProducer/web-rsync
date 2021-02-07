const fileChecksum = require('./build/Release/file-checksum.node');

// console.log(fileChecksum.sha256_checksum('./test-files/image.png'))
// console.log(fileChecksum.test('../history-intro/dist', '../biology-intro/dist'))
fileChecksum.test('../history-intro/dist', '../biology-intro/dist')