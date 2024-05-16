#include "typing.hpp"

ponomarev::Bracket::Bracket(char symbol):
  bracket(symbol)
{
  if (symbol == '+' || symbol == '-')
  {
    priority_ = 1;
  }
  else if (symbol == '*' || symbol == '/')
  {
    priority_ = 2;
  }
  else
  {
    priority_ = 0;
  }
}
}

bool ponomarev::isOpenBracket(char symbol)
{
  return (bracket_ == "(");
}

ponomarev::Operation::Operation(char elem):
  operation_(elem);
{}

void ponomarev::putOperation(char symbol)
{
  operation_ = symbol;
}

ponomarev::Operand::Operand():
  num(0)
{}

ponomarev::Operand::Operand(int num):
  num(num)
{}

void ponomarev::putValue(int value)
{
  num_ = value;
}

ponomarev::ExpressionElement::ExpressionElement():
  type(" "),
  brac(" "),
  operation(" "),
  operand(0)
{}

void ponomarev::ExpressionElement::putOperand(int value)
{
  operand.putValue(value);
  type = "Operand";
}

void ponomarev::ExpressionElement::putOperation(char symbol)
{
  operation.putOperation(symbol);
  type = "Operation";
}

void ponomarev::ExpressionElement::putBracket(char symbol)
{
  bracket.bracket = symbol;
  type = "Bracket";
}

const std::string ponomarev::ExpressionElement::getType() const
{
  return type;
}

const ponomarev::Operand & ponomarev::ExpressionElement::getOperand() const
{
  return operand;
}
const ponomarev::Operation & ponomarev::ExpressionElement::getOperation() const
{
  return operation;
}
const ponomarev::Bracket & ponomarev::ExpressionElement::getBracket() const
{
  return bracket;
}
