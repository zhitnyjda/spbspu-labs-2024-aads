#include "operands.hpp"
#include <stdexcept>
#include <limits>

miheev::Operand::Operand(long long val):
  value(val)
{}

miheev::Operand miheev::Operand::operator+(const miheev::Operand& rhs) const
{
  if (std::numeric_limits< long long >::max() - value < rhs.value)
  {
    throw std::logic_error("plus op has overflow\n");
  }
  if (std::numeric_limits< long long >::min() + value > rhs.value)
  {
    throw std::logic_error("plus op has underflow\n");
  }
  return miheev::Operand(value + rhs.value);
}
miheev::Operand miheev::Operand::operator-(const miheev::Operand& rhs) const
{
  if (std::numeric_limits< long long >::min() + value > rhs.value)
  {
    throw std::logic_error("minus op has underflow\n");
  }
  if (std::numeric_limits< long long >::max() - value < -rhs.value)
  {
    throw std::logic_error("minus op has overflow\n");
  }
  return miheev::Operand(value - rhs.value);
}
miheev::Operand miheev::Operand::operator*(const miheev::Operand& rhs) const
{
  if (std::numeric_limits< long long >::max() / value < rhs.value)
  {
    throw std::logic_error("multiply op has overflow\n");
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
