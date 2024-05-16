#ifndef COMPUTATIONAL_FUNCTIONS_HPP
#define COMPUTATIONAL_FUNCTIONS_HPP

#include "queue.hpp"
#include "typing.hpp"
#include <string>

namespace ponomarev
{
  void getPostfix(std::string expression, Queue< std::string > & postfix);
  bool isNum(const std::string & str);
  ExpressionElement getElem(std::string & expression);
}

#endif
