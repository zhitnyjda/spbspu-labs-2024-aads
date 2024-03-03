#include <iostream>
#include "doublelist.hpp"

using namespace kovshikov;
int main()
{
  std::cout << "hello";
  DoubleList<int> dl;
  int i = 3;
  std::cout << "checking metods" << "\n";
  dl.pushFront(3);
  std::cout << dl.front();
  dl.pushFront(5);
  dl.pushFront(11);
  std::cout << dl.front();
  dl.pushBack(16);
  std::cout << dl.back() << "\n";
  dl.popFront();
  std::cout << dl.front() << "\n";
  std::cout << dl.back();
  dl.popBack();
  std::cout << dl.back();
  DoubleList<int> list;
  std::cout << "create new list" << "\n";
  std::cout << list.empty();
  std::cout << dl.empty() << "\n";
  list.pushFront(25);
  list.swap(dl);
  std::cout << list.front() << "\n" << dl.front();
  list.swap(dl);
  std::cout << list.front() << "\n" << dl.front() << dl.back() << "\n";
  dl.clear();
  std::cout << dl.empty();
}
