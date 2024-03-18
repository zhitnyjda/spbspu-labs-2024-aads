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
  return 0;
}
