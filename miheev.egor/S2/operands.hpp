#ifndef OPERANDS_HPP
#define OPERANDS_HPP

namespace miheev
{
  class Operand
  {
  public:
    Operand(long long val);
    Operand& operator+(const Operand& rhs);
    Operand& operator-(const Operand& rhs);
    Operand& operator*(const Operand& rhs);
    Operand& operator/(const Operand& rhs);
    Operand& operator%(const Operand& rhs);
    long long value;
  };
}


#endif