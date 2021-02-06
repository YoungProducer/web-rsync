#include "files-diff.h"

std::list<FileAction *> getFilesDiff(FilesMap *next, FilesMap prev)
{
    std::list<FileAction *> diff;

    for (const auto &e : *next)
    {
        FilesMap::iterator pair = prev.find(e.first);

        if (pair == prev.end())
        {
            diff.push_back(new FileAction(&e.first, ActionType::ADD));
        }
        else
        {
            if (e.second != pair->second)
            {
                diff.push_back(new FileAction(&e.first, ActionType::UPDATE));
            }
            prev.erase(pair);
        }
    }

    for (const auto &e : prev)
    {
        diff.push_back(new FileAction(&e.first, ActionType::REMOVE));
    }

    return diff;
}
