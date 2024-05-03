#ifndef EXPRESSION_ELEMENT_HPP
#define EXPRESSION_ELEMENT_HPP

#include "operations.hpp"
#include "operands.hpp"
#include "string"

namespace miheev
{
  struct element_t
  {
    element_t();
    element_t(const element_t&);
    element_t& operator=(const element_t&);
    ~element_t();
    Operand operand;
    Operation operation;
    Parenthesis parenthesis;
    std::string type;
  };
}

#endif