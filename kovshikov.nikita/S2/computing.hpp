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
  void getPostfix(doubleQ oldQ, doubleQ& newQ);
  long long getComputing(Queue< std::string > queue);//для одного выражения
  void getComputing(doubleQ data, Stack< long long >& result);// для всех выражений
  void output(std::ostream& out, Stack< long long > result);
}

#endif
