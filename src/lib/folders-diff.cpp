#include "folders-diff.h"

std::vector<FileAction *> get_folders_diff(FilesMap prev, FilesMap *next)
{
    std::vector<FileAction *> diff;

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

std::vector<FileAction *> get_folders_diff(std::string *prevPath, FilesMap *next)
{
    std::vector<FileAction *> diff;

    FilesMap prev = scan_dir(*prevPath);

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

std::vector<FileAction *> get_folders_diff(std::string *prevPath, std::string *nextPath)
{
    std::vector<FileAction *> diff;

    FilesMap prev = scan_dir(*prevPath);
    FilesMap next = scan_dir(*nextPath);

    for (const auto &e : next)
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