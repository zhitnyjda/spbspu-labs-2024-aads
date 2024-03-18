#include <iostream>
#include "doublelist.hpp"
#include <utility>

using namespace kovshikov;
int main()
{
  std::cout << "start checking DoubleList" << "\n";
  DoubleList<int> list;
  list.pushFront(3);
  list.pushFront(4);
  list.pushFront(7);
  list.remove(4);
  list.popFront();
  std::cout << list.front() << "\n";
  list.remove(4);
  std::cout << list.empty() << "\n";
  list.remove(3);
  std::cout << list.empty() << "\n";
  list.pushFront(2);
  list.pushFront(9);
  list.remove(9);
  std::cout << list.front() << "\n";
  return 0;
}
