#ifndef PROCESSINGFUNCTIONS_HPP
#define PROCESSINGFUNCTIONS_HPP
#include <istream>
#include <string>
#include "stack.hpp"

namespace redko
{
  bool isNumeric(const std::string & str);
  void processExpressions(std::istream & input, Stack< long long > & res);
}

#endif
