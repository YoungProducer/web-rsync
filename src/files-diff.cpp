#include "files-diff.h"

FileData *findPair(std::string path, std::vector<FileData> *source)
{
    bool hasPair = false;
    FileData *pair = nullptr;

    for (int i = 0, length = source->size(); i < length; i++)
    {
        FileData *dataToCheck = &source->at(i);
        if (dataToCheck->path == path)
        {
            hasPair = true;
            pair = dataToCheck;
        }
    }

    return pair;
}

std::vector<FileAction> *getFilesDiff(std::vector<FileData> *next, std::vector<FileData> *prev)
{
    std::vector<FileAction> *diff;

    for (int i = 0, length = next->size(); i < length; i++)
    {
        // if (next->at(i).checksum == )
    }
}
