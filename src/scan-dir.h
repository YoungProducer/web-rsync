#ifndef SCAN_DIR
#define SCAN_DIR

#include <string>
#include <filesystem>
#include <boost/unordered_map.hpp>

#include "./types/simple.h"
#include "sha256-checksum.h"

FilesMap scanDir(std::string path);

#endif // SCAN_DIR