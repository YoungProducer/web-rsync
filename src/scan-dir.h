#ifndef SCAN_DIR
#define SCAN_DIR

#include <string>
#include <vector>
#include <filesystem>

#include "./types/simple.h"
#include "sha256-checksum.h"

std::vector<FileData> scanDir(std::string path);

#endif // SCAN_DIR