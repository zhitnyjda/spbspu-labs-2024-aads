#ifndef INPUT_HPP
#define INPUT_HPP
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
namespace zheleznyakov
{
  void readLines(std::istream & input, Queue< std::string > & queue);
  void tokenize(std::string str, zheleznyakov::Stack< std::string > &dest);
}
#endif
