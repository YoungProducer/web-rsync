#include "string-to-number.h"

int stringToNumber(std::string *value)
{
    return 0;
}

std::string stringToStringNumber(std::string *value)
{
    std::string result = "";

    for (int i = 0, length = value->size(); i < length; i++)
    {
        int charInt = (int)value->at(i);
        result.append(numberToString(&charInt));
    }

    return result;
}