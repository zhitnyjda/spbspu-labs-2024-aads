#include "computationalFunctions.hpp"
#include "stack.hpp"

void ponomarev::getPostfix(std::string expression, Queue< std::string > & postfix)
{
}

bool ponomarev::isNum(const std::string & elem)
{
  return elem.find_first_not_of("0123456789") == std::string::npos && elem.size() != 0;
}
