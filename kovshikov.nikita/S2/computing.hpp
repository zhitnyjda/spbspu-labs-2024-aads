#ifndef COMPUTING_HPP
#define COMPUTING_HPP
#include "queue.hpp"
#include "stack.hpp"

namespace kovshikov
{
  using doubleQ = Queue< Queue< std::string > >;
  void readData(std::istream& in, Queue< std::string >& allData);
  void separateElements(std::string str, Queue< std::string >& queue);
  void separateElements(Queue< std::string > oldQ, doubleQ& sepQ);
  int getPriority(char c);
  bool isDigit(std::string str);
  void getPostfix(Queue< std::string >& oldQ, Queue< std::string >& newQ);
  void getAllPostfix(doubleQ oldQ, doubleQ newQ);
}

#endif
