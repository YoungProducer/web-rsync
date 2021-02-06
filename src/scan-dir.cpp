#include "scan-dir.h"

FilesMap scanDir(std::string path)
{
    FilesMap result;

    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        std::string filePath = file.path().string();

        // std::cout << filePath << std::endl;

        std::string checksum = SHA256_CHECKSUM(filePath.c_str());

        result.insert(std::make_pair(filePath, checksum));
    }

    return result;
}