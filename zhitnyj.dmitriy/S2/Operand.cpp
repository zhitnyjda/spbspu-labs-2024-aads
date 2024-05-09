#include "Operand.hpp"

Operand::Operand(long long val) : value(val)
{}

long long Operand::getValue() noexcept
{
  return value;
}

bool Operand::isOperator(char c) noexcept
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')';
}
