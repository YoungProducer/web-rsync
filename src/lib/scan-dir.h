#ifndef SCAN_DIR
#define SCAN_DIR

#include <vector>
#include <filesystem>
#include <boost/range.hpp>

#include "../types/simple.h"
#include "sha256-checksum.h"

std::vector<std::string> get_dir_content(std::string path);
void get_dir_content(std::string path, std::vector<std::string> *content);

FilesMap scan_dir(std::string path);

#endif // SCAN_DIR