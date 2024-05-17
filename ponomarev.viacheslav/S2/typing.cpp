#include "typing.hpp"

ponomarev::Bracket::Bracket(char symbol):
  bracket_(symbol)
{}

ponomarev::Operand::Operand():
  num_(0)
{}

ponomarev::Operand::Operand(long long num):
  num_(num)
{}

void ponomarev::Operand::putValue(long long value)
{
  num_ = value;
}

long long ponomarev::Operand::getValue()
{
  return num_;
}

ponomarev::Operation::Operation(char symbol):
  operation_(symbol)
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

void ponomarev::Operation::putOperation(char symbol)
{
  operation_ = symbol;
}

ponomarev::Operand ponomarev::Operation::useOperation(const Operand left, const Operand right) const
{
  Operand res;
  if (operation_ == '+')
  {
    res.num_ = left.num_ + right.num_;
    return res;
  }
  else if (operation_ == '-')
  {
    res.num_ = left.num_ - right.num_;
    return res;
  }
  else if (operation_ == '*')
  {
    res.num_ = left.num_ * right.num_;
    return res;
  }
  else if (operation_ == '/')
  {
    res.num_ = left.num_ / right.num_;
    return res;
  }
  else if (operation_ == '%')
  {
    res.num_ = left.num_ % right.num_;
    return res;
  }
  else
  {
    throw std::logic_error("Unsupported operation");
  }
}

ponomarev::ExpressionElement::ExpressionElement():
  type("none"),
  bracket('a'),
  operation('+'),
  operand(0)
{}

void ponomarev::ExpressionElement::putOperand(long long value)
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
  bracket.bracket_ = symbol;
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
