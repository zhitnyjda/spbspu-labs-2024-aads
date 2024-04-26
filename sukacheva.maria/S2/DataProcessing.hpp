#ifndef DATAPROCESSING_HPP
#define DATAPROCESSING_HPP
#include <iosfwd>
#include "Stack.hpp"
#include "Queue.hpp"
#include "DataTypes.hpp"

namespace sukacheva {
  Queue< std::string > inputStatement(std::istream& input);
  Queue< ElementOfStatement > makePostfix(Queue< std::string >& infix);
  long long calculate(Queue< ElementOfStatement >& postfix);
}
#endif
