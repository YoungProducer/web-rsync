const addon = require('../build/Release/file-checksum.node');

function FilesMap(map) {
    this.append = function(path, checksum) {
        return _addonInstance.append(path, checksum);
    }

    this.getValue = function() {
        return _addonInstance.getValue();
    }

    var _addonInstance = new addon.FilesMap(map);
}

module.exports = { FilesMap };