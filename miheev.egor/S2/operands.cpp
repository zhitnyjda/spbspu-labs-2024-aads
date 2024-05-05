#include "operands.hpp"
#include <stdexcept>
#include <limits>

miheev::Operand::Operand(long long val):
  value(val)
{}

miheev::Operand miheev::Operand::operator+(const miheev::Operand& rhs) const
{
  bool overflowIsPossible = value > 0 && rhs.value > 0;
  bool isOverflow = std::numeric_limits< long long >::max() - value < rhs.value;
  if ( overflowIsPossible && isOverflow)
  {
    throw std::logic_error("plus op has overflow\n");
  }
  bool underflowIsPossible = value < 0 && rhs.value < 0;
  bool isUnderflow = std::numeric_limits< long long >::min() - value > rhs.value;
  if (underflowIsPossible && isUnderflow)
  {
    throw std::logic_error("plus op has underflow\n");
  }
  return miheev::Operand(value + rhs.value);
}
miheev::Operand miheev::Operand::operator-(const miheev::Operand& rhs) const
{
  bool underflowIsPossible = value < 0 && rhs.value > 0;
  bool isUnderflow = std::numeric_limits< long long >::min() - value > -rhs.value;
  if ( underflowIsPossible && isUnderflow)
  {
    throw std::logic_error("minus op has underflow\n");
  }
  bool overflowIsPossbile = value > 0 && rhs.value < 0;
  bool isOverflow = std::numeric_limits< long long >::max() + value < -rhs.value;
  if (overflowIsPossbile && isOverflow)
  {
    throw std::logic_error("minus op has overflow\n");
  }
  return miheev::Operand(value - rhs.value);
}
miheev::Operand miheev::Operand::operator*(const miheev::Operand& rhs) const
{
  bool areSameSign = (value > 0 && rhs.value > 0) || (value < 0 && rhs.value < 0);
  bool isOverflow = std::numeric_limits< long long >::max() / std::abs(value) < std::abs(rhs.value);
  if (areSameSign && isOverflow)
  {
    throw std::logic_error("multiply op has overflow\n");
  }
  bool isUnderflow = std::abs(std::numeric_limits< long long >::min() / value) < std::abs(rhs.value);
  if (!areSameSign && isUnderflow)
  {
    throw std::logic_error("multiply op has underflow\n");
  }
  return miheev::Operand(value * rhs.value);
}
miheev::Operand miheev::Operand::operator/(const miheev::Operand& rhs) const
{
  if (rhs.value == 0)
  {
    throw std::logic_error("zero division error\n");
  }
  return miheev::Operand(value / rhs.value);
}
miheev::Operand miheev::Operand::operator%(const miheev::Operand& rhs) const
{
  return miheev::Operand((value % rhs.value + rhs.value) % rhs.value);
}
