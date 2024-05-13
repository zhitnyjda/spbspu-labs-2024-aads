#ifndef INPUT_FUNCTIONS_HPP
#define INPUT_FUNCTIONS_HPP

#include <istream>
#include <string>
#include "queue.hpp"

namespace ponomarev
{
  void inputExpressions(std::istream & input, Queue< std::string > & expressions);
}

#endif
