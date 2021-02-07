const { test, scanDir} = require('./build/Release/file-checksum.node');
const { FilesMap } = require('./lib/bindings');

// console.log(fileChecksum.sha256_checksum('./test-files/image.png'))
// console.log(fileChecksum.test('../history-intro/dist', '../biology-intro/dist'))
// fileChecksum.test('../history-intro/dist', '../biology-intro/dist')

console.time()
const result = scanDir('./test-files/next');

const fm = new FilesMap(result);
// fm.append('path', 'checksum');
console.log(fm.getValue())
fm.clear()
fm.from(result);
console.timeEnd()