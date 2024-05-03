#ifndef INPUT_PROCESSING_HPP
#define INPUT_PROCESSING_HPP

#include "stack.hpp"
#include "ios"

namespace miheev
{
  Stack< long long > processInput(std::istream&);
  long long calcLine(std::string); // here for test purposes. TODO: remove this line
}

#endif