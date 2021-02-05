#ifndef BIG_INT
#define BIG_INT

#define OPERATION_MAX_SIZE 8

#include <string>
#include <cstdlib>
#include <math.h>

#include "../utils/number-to-string.h"

/**
 * Amount of symbols(numbers) which are may be computed.
 * 
 * Example:
 * string: "1243543213211321"
 * 0: "13211321",
 * 1: "12435432"
 */

int selectNumbersForOperation(std::string *source);

class BigInt
{
public:
    BigInt();
    BigInt(std::string *);
    BigInt(std::string);
    BigInt(int *);
    BigInt(int);

    void setValue(std::string *);
    void setValue(int *);

    bool operator>(const BigInt &right);
    bool operator<(const BigInt &right);
    bool operator>=(const BigInt &right);
    bool operator<=(const BigInt &right);
    bool operator==(const BigInt &right);
    bool operator!=(const BigInt &right);

private:
    std::string value;
};

#endif // BIG_INT