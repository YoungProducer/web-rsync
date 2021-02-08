const { test, scanDir} = require('./build/Release/file-checksum.node');

// console.log(fileChecksum.sha256_checksum('./test-files/image.png'))
// console.log(fileChecksum.test('../history-intro/dist', '../biology-intro/dist'))
// fileChecksum.test('../history-intro/dist', '../biology-intro/dist')

console.time()
const result = scanDir('./test-files/next');

console.log(result);
console.timeEnd()