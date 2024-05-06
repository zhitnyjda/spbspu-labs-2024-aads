#ifndef COMPUTING_HPP
#define COMPUTING_HPP
#include "queue.hpp"

namespace kovshikov
{
  void readData(std::istream& in, Queue< std::string >& allData); // считывает всю информацию и записывает в очередь строк
  void separateElements(std::string str, Queue< std::string >& queue); // работает только для одной строки
  int getPriority(char c); //возвращает приоритет оператора
  bool isDigit(std::string str);
  void getPostfix(Queue< std::string >& oldQ, Queue< std::string >& newQ); //работает только для одной строки
}

#endif
