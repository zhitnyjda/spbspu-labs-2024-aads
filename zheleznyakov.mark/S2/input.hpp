#ifndef INPUT_HPP
#define INPUT_HPP
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
namespace zheleznyakov
{
  void readLines(std::istream & input, Queue< std::string > & queue);
  void tokenize(std::string str, Queue< std::string > & dest);
  bool isOperator(const std::string & token);
  int priority(const std::string & op);
  void infixToPostfix(Queue< std::string > & from, Queue< std::string > & to);
}
#endif
