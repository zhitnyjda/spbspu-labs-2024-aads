#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "list.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <cmath>

namespace nikiforov
{
  void convertToPostfix(std::string str, List< std::string >& Queue);

  void calculation(List< std::string >& Postfix, List< long long >& Result);

  void operation(std::string operand, List< long long >& Queue);

  size_t calculationPriority(std::string elemSeq);
}

#endif
