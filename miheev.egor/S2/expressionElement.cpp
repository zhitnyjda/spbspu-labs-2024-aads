#include "expressionElement.hpp"

miheev::element_t::element_t():
  type("none")
{}

miheev::element_t::element_t(const miheev::element_t& rhs)
{
  *this = rhs;
}

miheev::element_t& miheev::element_t::operator=(const miheev::element_t& rhs)
{
  operand = rhs.operand;
  operation = rhs.operation;
  parenthesis = rhs.parenthesis;
  type = rhs.type;
  return *this;
}

miheev::element_t::~element_t()
{}
