#ifndef DATAPROCESSING_HPP
#define DATAPROCESSING_HPP
#include <iosfwd>
#include "Stack.hpp"
#include "Queue.hpp"

namespace sukacheva {
  Queue< std::string > inputStatement(std::istream& input);
  Queue< std::string > makePostfix(Queue< std::string >& infix);
  bool isBinaryOperations(std::string example);
  bool isNumber(std::string example);
  size_t calculate(Queue< std::string >& postfix);
}
#endif