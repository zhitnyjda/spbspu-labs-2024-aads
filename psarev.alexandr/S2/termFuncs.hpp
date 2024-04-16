#ifndef TERMFUNCS_HPP
#define TERMFUNCS_HPP
#include <iostream>
#include <string>
#include "stack.hpp"

namespace psarev
{
  void inputTerm(Stack< std::string >& symbolSeq, std::istream& in);
}

#endif