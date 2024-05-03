#include "operands.hpp"

miheev::Operand::Operand(long long val):
  value(val)
{}

miheev::Operand miheev::Operand::operator+(const miheev::Operand& rhs) const
{
  return miheev::Operand(value + rhs.value);
}
miheev::Operand miheev::Operand::operator-(const miheev::Operand& rhs) const
{
  return miheev::Operand(value - rhs.value);
}
miheev::Operand miheev::Operand::operator*(const miheev::Operand& rhs) const
{
  return miheev::Operand(value * rhs.value);
}
miheev::Operand miheev::Operand::operator/(const miheev::Operand& rhs) const
{
  return miheev::Operand(value / rhs.value);
}
miheev::Operand miheev::Operand::operator%(const miheev::Operand& rhs) const
{
  return miheev::Operand(value % rhs.value);
}