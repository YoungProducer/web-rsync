const addon = require('../../build/Release/file-checksum.node');

function FilesMap(map) {
    this.append = function(path, checksum) {
        return _addonInstance.append(path, checksum);
    }

    this.getValue = function() {
        return _addonInstance.getValue();
    }

    this.clear = function() {
        return _addonInstance.clear();
    }

    this.from = function(map) {
        return _addonInstance.from(map)
    }

    var _addonInstance = new addon.FilesMapWrap(map);
}

module.exports = FilesMap;