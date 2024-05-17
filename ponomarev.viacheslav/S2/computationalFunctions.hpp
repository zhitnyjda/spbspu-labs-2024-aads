#ifndef COMPUTATIONAL_FUNCTIONS_HPP
#define COMPUTATIONAL_FUNCTIONS_HPP

#include "queue.hpp"
#include "typing.hpp"
#include <string>

namespace ponomarev
{
  void getPostfix(std::string expression, Postfix & postfix);
  bool isNum(const std::string & str);
  ExpressionElement getElem(std::string & expression);
  bool isOpenBracketUp(const Stack< ExpressionElement > & stack);
  bool shouldPushOpToStack(const Stack< ExpressionElement > & stack, const ExpressionElement & elem);
  int calculate(std::string & expression);
}

#endif
