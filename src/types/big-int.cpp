#include "big-int.h"

BigInt::BigInt()
{
    this->value = nullptr;
}

BigInt::BigInt(std::string *value)
{
    this->value = *value;
}

BigInt::BigInt(int *value)
{
    this->setValue(value);
}

void BigInt::setValue(std::string *value)
{
    this->value = *value;
}

void BigInt::setValue(int *value)
{
    this->value = numberToString(value);
}
