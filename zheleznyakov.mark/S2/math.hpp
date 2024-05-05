#ifndef MATH_HPP
#define MATH_HPP
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "input.hpp"
namespace zheleznyakov
{
  void processProblems(Queue< std::string > & problems);
  long long calculatePostfix(Queue< std::string > & expression);
}
#endif
