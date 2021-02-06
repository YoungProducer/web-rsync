#include "simple.h"

/** FileData */
FileData::FileData(std::string *path, std::string *checksum)
{
    this->path = *path;
    this->checksum = *checksum;
}

/** FileAction */
FileAction::FileAction(const std::string *path, ActionType type)
{
    this->path = *path;
    this->type = type;
}