#include "scan-dir.h"

std::vector<FileData> scanDir(std::string path)
{
    std::vector<FileData> result;

    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        std::string filePath = file.path().string();

        std::cout << filePath << std::endl;

        std::string checksum = SHA256_CHECKSUM(filePath.c_str());

        result.push_back(FileData(&filePath, &checksum));
    }

    return result;
}