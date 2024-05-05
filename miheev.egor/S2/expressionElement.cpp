#include "expressionElement.hpp"

miheev::element_t::element_t():
  type("none")
{}

miheev::element_t::element_t(const element_t& rhs)
{
  *this = rhs;
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
    operand = Operand(rhs.operand.value_);
  }
  else if (rhs.type == "parenthesis")
  {
    parenthesis = Parenthesis{rhs.parenthesis.parenthesis};
  }
  return *this;
}
