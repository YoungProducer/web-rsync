#include "folders-diff.h"

std::vector<FileAction *> get_folders_diff(boost::unordered_map<std::string, std::string> prev, boost::unordered_map<std::string, std::string> *next)
{
    std::vector<FileAction *> diff;

    for (const auto &e : *next)
    {
        boost::unordered_map<std::string, std::string>::iterator pair = prev.find(e.first);

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
