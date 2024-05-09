#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "ExpressionItem.hpp"

class Operand : public ExpressionItem
{
    long long value;

public:
    Operand(long long val) : value(val)
    {
    }

    long long getValue()
    {
      return value;
    }
};

#endif
