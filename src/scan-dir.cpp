#include "scan-dir.h"

FilesMap scanDir(std::string path)
{
    FilesMap result;

    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        std::string filePath = file.path().string();

        std::string checksum = SHA256_CHECKSUM(filePath.c_str());

        /** doesn't include "path" which passes from params */
        std::string relativePath = filePath.substr(filePath.find(path) + path.size());

        result.insert(std::make_pair(relativePath, checksum));
    }

    return result;
}