#ifndef BIG_INT
#define BIG_INT

#include <string>

#include "../utils/number-to-string.h"

class BigInt
{
public:
    BigInt();
    BigInt(std::string *);
    BigInt(int *);

    void setValue(std::string *);
    void setValue(int *);

private:
    std::string value;
};

#endif // BIG_INT