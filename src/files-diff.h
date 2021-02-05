#ifndef FILES_DIFF
#define FILES_DIFF

#include <string>
#include <vector>

struct FileData
{
    std::string path;
    std::string checksum;
};

enum ActionType
{
    UPDATE = 'UPDATE',
    REMOVE = 'REMOVE',
    ADD = 'ADD'
};

struct FileAction
{
    std::string path;
    ActionType type;
};

FileData *findPair(std::string path, std::vector<FileData> *source);

std::vector<FileAction> *getFilesDiff(std::vector<FileData> *next, std::vector<FileData> *prev);

#endif // FILES_DIFF