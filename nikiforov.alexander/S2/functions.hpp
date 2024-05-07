#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "stack.hpp"
#include "queue.hpp"
#include "dataTypes.hpp"

namespace nikiforov
{
  void convertToPostfix(std::string str, Queue< dataTypes >& Queue);

  void calculation(Queue< dataTypes >& Postfix, Stack< long long >& Result);

  void operations(std::string operand, Stack< long long >& stack);

  size_t calculationPriority(std::string elemSeq);
}

#endif
