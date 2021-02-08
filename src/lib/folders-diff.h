#ifndef FILES_DIFF
#define FILES_DIFF

#include <string>
#include <vector>
#include <boost/unordered_map.hpp>

#include "scan-dir.h"
#include "../types/simple.h"

std::vector<FileAction *> get_folders_diff(FilesMap prev, FilesMap *next);
std::vector<FileAction *> get_folders_diff(std::string *prevPath, FilesMap *next);

#endif // FILES_DIFF