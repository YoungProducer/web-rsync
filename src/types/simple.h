#ifndef SIMPLE
#define SIMPLE

#include <string>
#include <unordered_map>

struct FileData
{
    std::string path;
    std::string checksum;

    FileData(std::string *path, std::string *checksum);
};

enum ActionType
{
    UPDATE = 1,
    REMOVE = 2,
    ADD = 3
};

struct FileAction
{
    std::string path;
    std::string type;

    FileAction(const std::string *path, ActionType type);
};

typedef std::unordered_map<std::string, std::string> FilesMap;

std::string get_type_name(ActionType type);

#endif // SIMPLE