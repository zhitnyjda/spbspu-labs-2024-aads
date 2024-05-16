#include "typing.hpp"

ponomarev::Bracket::Bracket(char symbol):
  bracket(symbol)
{}

bool ponomarev::isOpenBracket(char symbol)
{
  return (symbol == "(");
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
