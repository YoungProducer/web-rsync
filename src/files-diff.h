#ifndef FILES_DIFF
#define FILES_DIFF

#include <string>
#include <vector>
#include <boost/unordered_map.hpp>

#include "./types/simple.h"

FileData findPair(std::string path, std::vector<FileData> *source);

std::vector<FileAction> getFilesDiff(FilesMap *next, FilesMap *prev);

#endif // FILES_DIFF