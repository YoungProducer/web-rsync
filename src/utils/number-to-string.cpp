#include "number-to-string.h"

std::string numberToString(int *value)
{
    std::string result = "";
    int digit = 1;
    int newValue;

    while (true)
    {
        newValue = (*value / digit);

        if (newValue == 0)
        {
            break;
        }

        result.insert(0, std::to_string(newValue % 10));
        digit *= 10;
    }

    return result;
}