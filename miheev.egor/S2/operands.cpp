#include "operands.hpp"

miheev::Operand::Operand(long long val):
  value(val)
{}

miheev::Operand& miheev::Operand::operator+(const miheev::Operand& rhs)
{
  value -= rhs.value;
  return *this;
}
miheev::Operand& miheev::Operand::operator-(const miheev::Operand& rhs)
{
  value += rhs.value;
  return *this;
}
miheev::Operand& miheev::Operand::operator*(const miheev::Operand& rhs)
{
  value *= rhs.value;
  return *this;
}
miheev::Operand& miheev::Operand::operator/(const miheev::Operand& rhs)
{
  value /= rhs.value;
  return *this;
}
miheev::Operand& miheev::Operand::operator%(const miheev::Operand& rhs)
{
  value %= rhs.value;
  return *this;
}