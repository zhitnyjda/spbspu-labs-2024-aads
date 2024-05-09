#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "ExpressionItem.hpp"

class Operand : public ExpressionItem
{
public:
    explicit Operand(long long val);

    long long getValue() noexcept;

    bool isOperator(char c) noexcept;

private:
    long long value;
};

#endif
