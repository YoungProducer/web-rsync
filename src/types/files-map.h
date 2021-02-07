#ifndef _FILES_MAP_H_
#define _FILES_MAP_H_

#include <string>
#include <boost/unordered_map.hpp>

#include "../utils/type-transform.h"

typedef boost::unordered_map<std::string, std::string> FilesMapShorthand;

class FilesMap
{
public:
    FilesMap(){};
    FilesMap(FilesMapShorthand &map);

    void append(std::string path, std::string checksum);
    void append(std::pair<std::string, std::string> pair);

    void remove(FilesMapShorthand::iterator it);

    void clear();

    FilesMapShorthand *get_value();

protected:
    FilesMapShorthand _value;
};

#endif // _FILES_MAP_H_