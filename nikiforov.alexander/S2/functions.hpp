#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "stack.hpp"
#include "queue.hpp"
#include "dataTypes.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <cmath>

namespace nikiforov
{
  void convertToPostfix(std::string str, Queue< dataTypes >& Queue);

  void calculation(Queue< dataTypes >& Postfix, List< long long >& Result);

  void operations(std::string operand, Stack< long long >& stack);

  size_t calculationPriority(std::string elemSeq);

}

#endif
