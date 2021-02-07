#include "files-map.h"

FilesMap::FilesMap(FilesMapShorthand &map)
    : _value(map)
{
}

void FilesMap::append(std::string path, std::string checksum)
{
    this->_value.insert(std::make_pair(path, checksum));
}

void FilesMap::append(std::pair<std::string, std::string> pair)
{
    this->_value.insert(pair);
}

void FilesMap::remove(FilesMapShorthand::iterator it)
{
    this->_value.erase(it);
}

void FilesMap::clear()
{
    this->_value.clear();
}

FilesMapShorthand *FilesMap::get_value()
{
    return &(this->_value);
}
