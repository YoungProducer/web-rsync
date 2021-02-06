#ifndef SCAN_DIR
#define SCAN_DIR

#include <filesystem>
#include <boost/unordered_map.hpp>

#include "../types/simple.h"
#include "sha256-checksum.h"

FilesMap scan_dir(std::string path);

#endif // SCAN_DIR