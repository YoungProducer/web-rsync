#include "simple.h"

/** FilData */
FileData::FileData(std::string *path, std::string *checksum)
{
    this->path = *path;
    this->checksum = *checksum;
}