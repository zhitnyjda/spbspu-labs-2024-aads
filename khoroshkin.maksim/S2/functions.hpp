#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>
#include "stack.hpp"

namespace khoroshkin
{
  void inputInfix(std::istream & in, Stack< std::string > & expressions);
  long long calc(std::string str);
  std::string getToken(const std::string & str, size_t & pos);
  std::string readOperand(std::string str, size_t & pos);
  char readOperation(std::string str, size_t & pos);
  void skipWhitespace(std::string str, size_t & pos);
  bool isDigit(const std::string & str);
}

#endif
