#include "computationalFunctions.hpp"
#include "stack.hpp"
#include "cutFunctions.hpp"

void ponomarev::getPostfix(std::string expression, Queue< std::string > & postfix)
{
  Stack< ExpressionElement > stack;
  Queue< ExpressionElement > queue;
  while (!(expression.empty()))
  {
    ExpressionElement elem = getElem(expression);
  }
}

bool ponomarev::isNum(const std::string & elem)
{
  return elem.find_first_not_of("0123456789") == std::string::npos && elem.size() != 0;
}

ponomarev::ExpressionElement ponomarev::getElem(std::string & expression)
{
  ponomarev::ExpressionElement elem;
  std::string arg = getName(expression);
  if (isNum(arg))
  {
    elem.putOperand(std::stoi(arg));
  }
  else if (arg == "+" || arg == "-" || arg == "%" || arg == "*" || arg == "/")
  {
    elem.putOperation(arg[0]);
  }
  else if (arg == "(" || arg == ")")
  {
    elem.putBracket(arg[0]);
  }
  else
  {
    throw std::invalid_argument("Error: wrong expression");
  }
  return elem;
}
