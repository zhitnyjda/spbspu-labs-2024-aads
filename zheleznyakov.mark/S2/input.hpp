#ifndef INPUT_HPP
#define INPUT_HPP
#include <fstream>
#include "queue.hpp"
namespace zheleznyakov
{
  void readLines(std::istream & input, Queue< std::string > & queue);
}
#endif
