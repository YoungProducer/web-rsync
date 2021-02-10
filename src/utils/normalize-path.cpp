#include "normalize-path.h"

std::string normalize_path(std::string path)
{
    std::string result = path;

    int length = result.size();

    if (result.at(length - 1) == '/')
    {
        result.erase(length - 1);
    }

    return result;
}

void normalize_path(std::string *path)
{
    int length = path->size();

    if (path->at(length - 1) == '/')
    {
        path->erase(length - 1);
    }
}