#include "expressionElement.hpp"

miheev::element_t::element_t():
  type("none")
{}

miheev::element_t::element_t(const element_t& rhs)
{
  *this = rhs;
}

miheev::Operand miheev::element_t::getOperand() const
{
  return operand;
}
miheev::Operation miheev::element_t::getOperation() const
{
  return operation;
}
miheev::Parenthesis miheev::element_t::getParenthesis() const
{
  return parenthesis;
}
std::string miheev::element_t::getType() const
{
  return type;
}

void miheev::element_t::setOperand(const miheev::Operand& rhs)
{
  operand = rhs;
}
void miheev::element_t::setOperation(const miheev::Operation& rhs)
{
  operation = rhs;
}
void miheev::element_t::setParenthesis(const miheev::Parenthesis& rhs)
{
  parenthesis = rhs;
}
void miheev::element_t::setType(std::string rhs)
{
  type = rhs;
}

miheev::element_t& miheev::element_t::operator=(const element_t& rhs)
{
  type = rhs.type;
  if (rhs.type == "operation")
  {
    operation = Operation(rhs.operation.operation);
  }
  else if (rhs.type == "operand")
  {
    operand = Operand(rhs.operand.getValue());
  }
  else if (rhs.type == "parenthesis")
  {
    parenthesis = Parenthesis{rhs.parenthesis.parenthesis};
  }
  return *this;
}
