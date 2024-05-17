#ifndef TYPING_HPP
#define TYPING_HPP

#include "queue.hpp"
#include "stack.hpp"

namespace ponomarev
{
  struct Bracket
  {
    explicit Bracket(char symbol);

    char bracket_;
  };

  struct Operand
  {
    Operand();
    explicit Operand(int num);

    void putValue(int value);
    int getValue();

    int num_;
  };

  struct Operation
  {
    explicit Operation(char symbol);

    void putOperation(char symbol);
    Operand useOperation(const Operand left, const Operand right) const;

    char operation_;
    int priority_;
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
    Queue< ExpressionElement > postfix_;
  };
}

#endif
