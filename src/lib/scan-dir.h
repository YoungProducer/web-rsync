#ifndef SCAN_DIR
#define SCAN_DIR

#include <iostream>
#include <vector>
#include <filesystem>
#include <unordered_map>

#include "sha256-checksum.h"
#include "../utils/normalize-path.h"
#include "../types/simple.h"

std::vector<std::string> get_dir_content(std::string path, bool excludeDirs);
void get_dir_content(std::string path, std::vector<std::string> *content, bool excludeDirs);

FilesMap scan_dir(std::string path);

#endif // SCAN_DIR