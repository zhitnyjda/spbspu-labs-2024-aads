#include "expressionElement.hpp"

miheev::element_t::element_t():
  type("none")
{}

miheev::element_t::element_t(const miheev::element_t& rhs)
{
  operand = rhs.operand;
  operation = rhs.operation;
  parenthesis = rhs.parenthesis;
  type = rhs.type;
}

miheev::element_t::~element_t()
{}
