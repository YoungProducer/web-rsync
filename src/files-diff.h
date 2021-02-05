#ifndef FILES_DIFF
#define FILES_DIFF

#include <string>
#include <vector>

#include "./types/simple.h"

FileData findPair(std::string path, std::vector<FileData> *source);

std::vector<FileAction> getFilesDiff(std::vector<FileData> *next, std::vector<FileData> *prev);

#endif // FILES_DIFF