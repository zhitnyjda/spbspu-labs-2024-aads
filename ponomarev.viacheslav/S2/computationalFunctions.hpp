#ifndef COMPUTATIONAL_FUNCTIONS_HPP
#define COMPUTATIONAL_FUNCTIONS_HPP

#include "queue.hpp"
#include <string>

namespace ponomarev
{
  void getPostfix(std::string expression, Queue< std::string > & postfix);
  bool isNum(const std::string & str);
}

#endif
