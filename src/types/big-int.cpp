#include "big-int.h"

/** HELPERS FUNCTIONS */

int selectNumbersForOperation(std::string *source)
{
    short numbersToSelect = source->size() < OPERATION_MAX_SIZE ? source->size() : OPERATION_MAX_SIZE;

    return stoi(source->substr(source->size() - numbersToSelect));
}

/** CONSTRUCTORS */

BigInt::BigInt()
{
    this->value = nullptr;
}

BigInt::BigInt(std::string *value)
{
    this->value = *value;
}

BigInt::BigInt(std::string value)
{
    this->value = value;
}

BigInt::BigInt(int *value)
{
    this->setValue(value);
}

BigInt::BigInt(int value)
{
    this->setValue(&value);
}

/** METHODS */

void BigInt::setValue(std::string *value)
{
    this->value = *value;
}

void BigInt::setValue(int *value)
{
    this->value = numberToString(value);
}

bool BigInt::operator>(const BigInt &right)
{
    BigInt left = *this;
    std::string leftValue = left.value;
    std::string rightValue = right.value;

    bool isTrue = true;

    if (leftValue == rightValue)
    {
        isTrue = false;
    }
    else
    {
        if (leftValue.size() == rightValue.size())
        {
            short leftSizeInOps = ceil((float)leftValue.size() / (float)OPERATION_MAX_SIZE);
            short rightSizeInOps = ceil((float)rightValue.size() / (float)OPERATION_MAX_SIZE);

            if (leftSizeInOps == rightSizeInOps)
            {
                for (int i = leftSizeInOps; i > 0; i--)
                {
                    int leftPart = selectNumbersForOperation(&leftValue);
                    int rightPart = selectNumbersForOperation(&rightValue);

                    if (leftPart < rightPart)
                    {
                        isTrue = false;
                        break;
                    }
                }
            }
            else
            {
                isTrue = leftSizeInOps > rightSizeInOps;
            }
        }
        else
        {
            isTrue = leftValue.size() > rightValue.size();
        }
    }

    return isTrue;
}

bool BigInt::operator<(const BigInt &right)
{
    BigInt left = *this;
    std::string leftValue = left.value;
    std::string rightValue = right.value;

    bool isTrue = true;

    if (leftValue == rightValue)
    {
        isTrue = false;
    }
    else
    {
        if (leftValue.size() == rightValue.size())
        {
            short leftSizeInOps = ceil((float)leftValue.size() / (float)OPERATION_MAX_SIZE);
            short rightSizeInOps = ceil((float)rightValue.size() / (float)OPERATION_MAX_SIZE);

            if (leftSizeInOps == rightSizeInOps)
            {
                for (int i = leftSizeInOps; i > 0; i--)
                {
                    int leftPart = selectNumbersForOperation(&leftValue);
                    int rightPart = selectNumbersForOperation(&rightValue);

                    if (leftPart > rightPart)
                    {
                        isTrue = false;
                        break;
                    }
                }
            }
            else
            {
                isTrue = leftSizeInOps < rightSizeInOps;
            }
        }
        else
        {
            isTrue = leftValue.size() < rightValue.size();
        }
    }

    return isTrue;
}

bool BigInt::operator<=(const BigInt &right)
{
    BigInt left = *this;
    std::string leftValue = left.value;
    std::string rightValue = right.value;

    bool isTrue = true;

    if (leftValue == rightValue)
    {
        isTrue = true;
    }
    else
    {
        if (leftValue.size() == rightValue.size())
        {
            short leftSizeInOps = ceil((float)leftValue.size() / (float)OPERATION_MAX_SIZE);
            short rightSizeInOps = ceil((float)rightValue.size() / (float)OPERATION_MAX_SIZE);

            if (leftSizeInOps == rightSizeInOps)
            {
                for (int i = leftSizeInOps; i > 0; i--)
                {
                    int leftPart = selectNumbersForOperation(&leftValue);
                    int rightPart = selectNumbersForOperation(&rightValue);

                    if (leftPart > rightPart)
                    {
                        isTrue = false;
                        break;
                    }
                }
            }
            else
            {
                isTrue = leftSizeInOps < rightSizeInOps;
            }
        }
        else
        {
            isTrue = leftValue.size() < rightValue.size();
        }
    }

    return isTrue;
}

bool BigInt::operator>=(const BigInt &right)
{
    BigInt left = *this;
    std::string leftValue = left.value;
    std::string rightValue = right.value;

    bool isTrue = true;

    if (leftValue == rightValue)
    {
        isTrue = true;
    }
    else
    {
        if (leftValue.size() == rightValue.size())
        {
            short leftSizeInOps = ceil((float)leftValue.size() / (float)OPERATION_MAX_SIZE);
            short rightSizeInOps = ceil((float)rightValue.size() / (float)OPERATION_MAX_SIZE);

            if (leftSizeInOps == rightSizeInOps)
            {
                for (int i = leftSizeInOps; i > 0; i--)
                {
                    int leftPart = selectNumbersForOperation(&leftValue);
                    int rightPart = selectNumbersForOperation(&rightValue);

                    if (leftPart < rightPart)
                    {
                        isTrue = false;
                        break;
                    }
                }
            }
            else
            {
                isTrue = leftSizeInOps > rightSizeInOps;
            }
        }
        else
        {
            isTrue = leftValue.size() > rightValue.size();
        }
    }

    return isTrue;
}

bool BigInt::operator==(const BigInt &right)
{
    return this->value == right.value;
}

bool BigInt::operator!=(const BigInt &right)
{
    return this->value != right.value;
}
