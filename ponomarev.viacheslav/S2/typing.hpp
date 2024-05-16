#ifndef TYPING_HPP
#define TYPING_HPP

#include "queue.hpp"
#include "stack.hpp"

namespace ponomarev
{
  struct Bracket
  {
    explicit Bracket(char symbol);

    bool isOpenBracket();

    char bracket_;
  };

  struct Operation
  {
    explicit Operation(char elem);

    void putOperation(char symbol);

    char operation_;
    int priority_;
  };

  struct Operand
  {
    Operand();
    explicit Operand(int num);

    void putValue(int value);

    int num_;
  };

  struct ExpressionElement
  {
    ExpressionElement();

    void putOperand(int value);
    void putOperation(char symbol);
    void putBracket(char symbol);
    const std::string getType() const;
    const Operand & getOperand() const;
    const Operation & getOperation() const;
    const Bracket & getBracket() const;

    std::string type;
    Bracket bracket;
    Operation operation;
    Operand operand;
  };

  struct Postfix
  {
    Queue< ExpressionElement > postfix;
  };
}

#endif
