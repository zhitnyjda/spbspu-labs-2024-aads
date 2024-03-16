
#include <iostream>
#include "doublelist.hpp"

using namespace kovshikov;
int main()
{
  std::cout << "start checking DoubleList" << "\n";
  DoubleList<int> list;
  list.pushFront(7);
  std::cout << list.front() << "\n";
  list.pushFront(9);
  std::cout << list.front() << "\n";
  list.pushBack(2);
  std::cout << list.back() << "\n";
  list.pushBack(0);
  std::cout << list.back() << "\n";
  std::cout << "begin: " << list.front() << " end: " << list.back() << "\n";
  list.popFront();
  list.popBack();
  std::cout << "begin: " << list.front() << " end: " << list.back() << "\n";
  list.popFront();
  list.popBack();
  std::cout << "type";
  std::cout << "bool is empty? " << list.empty() << "\n";
  return 0;
}
