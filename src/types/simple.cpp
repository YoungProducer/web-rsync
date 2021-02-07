#include "simple.h"

/** FileData */
FileData::FileData(std::string *path, std::string *checksum)
{
    this->path = *path;
    this->checksum = *checksum;
}

/** FileAction */
std::string get_type_name(ActionType type)
{
    switch (type)
    {
    case 1:
        return "UPDATE";
        break;

    case 2:
        return "REMOVE";
        break;

    case 3:
        return "ADD";
        break;

    default:
        return NULL;
        break;
    }
}

FileAction::FileAction(const std::string *path, ActionType type)
{
    this->path = *path;
    this->type = get_type_name(type);
}