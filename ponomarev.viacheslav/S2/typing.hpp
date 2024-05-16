#ifndef TYPING_HPP
#define TYPING_HPP

#include "queue.hpp"
#include "stack.hpp"

namespace ponomarev
{
  struct Bracket
  {
    explicit Bracket(char symbol);

    bool isBracket(char symbol);
    bool isOpenBracket(char symbol);

    char bracket;
  }

  struct Operation
  {
    explicit Operation(char elem);

    char operation_;
  }

  struct Operand
  {
    Operand();
    explicit Operand(int num);

    int num;
  }

  struct ExpressionElement
  {
    Bracket bracket_;
    Operand operand_;
    Operation operation_;
    std::string type_;
  };

  struct Postfix
  {
    Queue< ExpressionElement > postfix;
  }
}

#endif
