#ifndef COMPUTING_HPP
#define COMPUTING_HPP
#include "queue.hpp"
#include "stack.hpp"

namespace kovshikov
{
  void readData(std::istream& in, Queue< std::string >& allData);
  void separateElements(std::string str, Queue< std::string >& queue);
  int getPriority(char c);
  bool isDigit(std::string str);
  void getPostfix(Queue< std::string >& oldQ, Queue< std::string >& newQ);
}

#endif
