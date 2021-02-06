#include "scan-dir.h"

std::vector<std::string> get_dir_content(std::string path)
{
    std::vector<std::string> result;

    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        result.push_back(file.path().string());
    }

    return result;
}

void get_dir_content(std::string path, std::vector<std::string> *content)
{
    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        content->push_back(file.path().string());
    }
}

FilesMap scan_dir(std::string path)
{
    FilesMap result;
    std::vector<std::string> dir_content;

    if (std::filesystem::is_directory(path))
    {
        get_dir_content(path, &dir_content);

        for (int i = 0, length = dir_content.size(); i < length; i++)
        {
            std::string curr_path = dir_content[i];
            std::string checksum = SHA256_CHECKSUM(path.c_str());

            /** doesn't include "path" which passes from params */
            std::string relative_path = curr_path.substr(curr_path.find(path) + path.size());

            result.insert(std::make_pair(relative_path, checksum));
        }
    }

    return result;
}