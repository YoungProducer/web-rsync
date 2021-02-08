const { test, scanDir, getFoldersDiff } = require('./build/Release/file-checksum.node');

// console.log(fileChecksum.sha256_checksum('./test-files/image.png'))
// console.log(fileChecksum.test('../history-intro/dist', '../biology-intro/dist'))
// fileChecksum.test('../history-intro/dist', '../biology-intro/dist')

console.time()
// const prev = scanDir('./test-files/prev');
const next = scanDir('../biology-intro/dist');

// console.log(prev, next)

const diff = getFoldersDiff('../biology-intro/dist', next);

console.log(diff);
console.timeEnd()