#ifndef FILES_DIFF
#define FILES_DIFF

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/container/list.hpp>

#include "../types/simple.h"

std::list<FileAction *> getFilesDiff(FilesMap *next, FilesMap prev);

#endif // FILES_DIFF