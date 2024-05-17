#ifndef TYPES_HPP
#define TYPES_HPP
#include "stack.hpp"

namespace mihalchenko
{
  struct CalcRez
  {
    CalcRez() = default;
    CalcRez(long long value);
    CalcRez operator+(const CalcRez &rhs);
    CalcRez operator-(const CalcRez &rhs);
    CalcRez operator*(const CalcRez &rhs);
    CalcRez operator/(const CalcRez &rhs);
    CalcRez operator%(const CalcRez &rhs);
    bool operator==(const char &rhs) const;
    long long resultCalc;
  };

  struct Parenthesis
  {
    char parenthesis;
  };

  struct FinalTransform
  {
    bool calculate();
    Stack< CalcRez > calcRezult;
    Stack< char > commands;
  };
}

#endif
