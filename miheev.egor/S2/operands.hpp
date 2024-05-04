#ifndef OPERANDS_HPP
#define OPERANDS_HPP

namespace miheev
{
  class Operand
  {
  public:
    Operand() = default;
    explicit Operand(long long val);
    Operand operator+(const Operand& rhs) const;
    Operand operator-(const Operand& rhs) const;
    Operand operator*(const Operand& rhs) const;
    Operand operator/(const Operand& rhs) const;
    Operand operator%(const Operand& rhs) const;
    long long value;
  };
}


#endif
