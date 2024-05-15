#ifndef COMPUTATIONAL_FUNCTIONS_HPP
#define COMPUTATIONAL_FUNCTIONS_HPP

#include "queue.hpp"
#include <string>

namespace ponomarev
{
  void getPostfix(std::string expression, Queue< std::string > & postfix);
  int calculate(Queue< std::string > & postfix);
}

#endif
