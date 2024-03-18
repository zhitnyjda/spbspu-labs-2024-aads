#include <iostream>
#include "doublelist.hpp"
#include <utility>

using namespace kovshikov;
int main()
{
  std::cout << "start checking DoubleList" << "\n";
  DoubleList<int> list;
  list.pushFront(2);
  list.pushFront(5);
  DoubleList<int> newList(std::move(list));
  std::cout << newList.front() << " " << newList.back() << "\n";
  newList.clear();
  newList = std::move(list);
  std::cout << newList.front() << " " << newList.back() << "\n";
  return 0;
}
