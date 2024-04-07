#ifndef EXPRESSIONTYPES_HPP
#define EXPRESSIONTYPES_HPP
#include <string>
#include "queue.hpp"

namespace redko
{
  struct Operation
  {
    bool operator>(const Operation & rhs) const;
    bool operator>=(const Operation & rhs) const;
    bool operator<(const Operation & rhs) const;
    bool operator<=(const Operation & rhs) const;

    char operation;
  };

  struct Operand
  {
    Operand():
      value(0)
    {}
    explicit Operand(long long val):
      value(val)
    {}

    Operand operator+(const Operand & rhs);
    Operand operator-(const Operand & rhs);
    Operand operator*(const Operand & rhs);
    Operand operator/(const Operand & rhs);
    Operand operator%(const Operand & rhs);

    long long value;
  };

  struct Bracket
  {
    char bracket;
  };

  enum type_t
  {
    none,
    operation,
    operand,
    bracket
  };

  struct ExprElem
  {
    ExprElem():
      elem(),
      type(none)
    {}
    union expr_t
    {
      expr_t() {}
      ~expr_t() {}

      Operation operation;
      Operand operand;
      Bracket bracket;
    };
    expr_t elem;
    type_t type;
  };

  struct PostfixElem
  {
    PostfixElem():
      elem(),
      type(none)
    {}
    PostfixElem(ExprElem eElem):
      type(eElem.type)
    {
      if (eElem.type == operand)
      {
        elem.operand = eElem.elem.operand;
      }
      else if (eElem.type == operation)
      {
        elem.operation = eElem.elem.operation;
      }
    }
    union postfix_t
    {
      postfix_t() {}
      ~postfix_t() {}

      Operation operation;
      Operand operand;
    };
    postfix_t elem;
    type_t type;
  };
}

#endif
