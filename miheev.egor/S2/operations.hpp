#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "operands.hpp"

namespace miheev
{
  class Operation
  {
  public:
    Operation() = default;
    Operation(char);
    bool operator<(const Operation& rhs) const;
    bool operator<=(const Operation& rhs) const;
    bool operator==(const Operation& rhs) const;
    bool operator>=(const Operation& rhs) const;
    bool operator>(const Operation& rhs) const;
    Operand implement(const Operand& lhs, const Operand& rhs) const;
    char operation;
  private:
    int priority_;
  };

  struct Parenthesis
  {
    char parenthesis;
  };
}

#endif