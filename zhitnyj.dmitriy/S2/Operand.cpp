#include "Operand.hpp"

Operand::Operand(long long val) : value(val)
{
}

long long Operand::getValue()
{
  return value;
}

bool Operand::isOperator()
{
  return false;
}

bool Operand::isOperand()
{
  return true;
}
