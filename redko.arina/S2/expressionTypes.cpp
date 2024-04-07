#include "expressionTypes.hpp"
#include <limits>
#include "processingFunctions.hpp"

bool redko::Operation::operator>(const Operation & rhs) const
{
  return operation != '+' && operation != '-' && rhs.operation != '*' && rhs.operation != '/' && rhs.operation != '%';
}
bool redko::Operation::operator>=(const Operation & rhs) const
{
  return !(*this < rhs);
}
bool redko::Operation::operator<(const Operation & rhs) const
{
  return (operation == '+' || operation == '-') && (rhs.operation == '*' || rhs.operation == '/' || rhs.operation == '%');
}
bool redko::Operation::operator<=(const Operation & rhs) const
{
  return !(*this > rhs);
}

redko::Operand redko::Operand::operator+(const Operand & rhs)
{
  if (rhs.value > 0 && value > 0 && (rhs.value > std::numeric_limits< long long >::max() - value))
  {
    throw std::overflow_error("Error: unable to calculate due to overflow");
  }
  if (rhs.value < 0 && value < 0 && (rhs.value < std::numeric_limits< long long >::min() - value))
  {
    throw std::underflow_error("Error: unable to calculate due to underflow");
  }
  return Operand(value + rhs.value);
}

redko::Operand redko::Operand::operator-(const Operand & rhs)
{
  if (value > 0 && rhs.value < 0 && (value > std::numeric_limits< long long >::max() + rhs.value))
  {
    throw std::overflow_error("Error: unable to calculate due to overflow");
  }
  if (value < 0 && rhs.value > 0 && (value < std::numeric_limits< long long >::min() + rhs.value))
  {
    throw std::underflow_error("Error: unable to calculate due to underflow");
  }
  return Operand(value - rhs.value);
}

redko::Operand redko::Operand::operator*(const Operand & rhs)
{
  if (((value > 0 && rhs.value > 0) || (value < 0 && rhs.value < 0)) && (abs(rhs.value) > abs(std::numeric_limits< long long >::max() / value)))
  {
    throw std::overflow_error("Error: unable to calculate due to overflow");
  }
  if (((value > 0 && rhs.value < 0) || (value < 0 && rhs.value > 0)) && (abs(rhs.value) > abs(std::numeric_limits< long long >::min() / value)))
  {
    throw std::underflow_error("Error: unable to calculate due to underflow");
  }
  return Operand(value * rhs.value);
}

redko::Operand redko::Operand::operator/(const Operand & rhs)
{
  if (rhs.value == 0)
  {
    throw std::logic_error("Error: division by 0");
  }
  return Operand(value / rhs.value);
}

redko::Operand redko::Operand::operator%(const Operand & rhs)
{
  if (rhs.value == 0)
  {
    throw std::logic_error("Error: mod by 0");
  }
  return Operand((value % rhs.value + rhs.value) % rhs.value);
}
