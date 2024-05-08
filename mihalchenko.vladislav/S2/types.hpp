#ifndef TYPES_HPP
#define TYPES_HPP
#include "stack.hpp"
#include <set>

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
    long long resultCalc;
  };

  struct finalTransform
  {
    bool calculate();
    Stack<CalcRez> calcRezult;
    Stack<char> commands;
  };
}

#endif
