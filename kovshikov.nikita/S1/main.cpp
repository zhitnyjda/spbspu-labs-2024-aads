
#include <iostream>
#include "doublelist.hpp"

using namespace kovshikov;
int main()
{
  std::cout << "start checking DoubleList" << "\n";
  DoubleList<int> list;
  list.pushFront(2);
  list.pushFront(5);
  DoubleList<int> newList(list);
  std::cout << newList.front() << " " << newList.back() << "\n";
















  /*DoubleList<int> list;
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
  std::cout << "bool is empty? " << list.empty() << "\n";
  list.pushFront(3);
  list.pushBack(4);
  std::cout << "begin: " << list.front() << " end: " << list.back() << "\n";
  list.popFront();
  list.popBack();
  std::cout << "bool is empty? " << list.empty() << "\n";
  list.pushFront(1);
  list.pushFront(2);
  list.pushFront(3);
  list.pushBack(4);
  list.clear();
  std::cout << "bool is empty? " << list.empty() << "\n";
  list.pushFront(25);
  list.pushFront(27);
  DoubleList<int> newList;
  newList.pushFront(98);
  newList.pushFront(99);
  std::cout << "begin: " << list.front() << " end: " << list.back() << "\n";
  std::cout << "begin: " << newList.front() << " end: " << newList.back() << "\n";
  list.swap(newList);
  std::cout << "begin: " << list.front() << " end: " << list.back() << "\n";
  std::cout << "begin: " << newList.front() << " end: " << newList.back() << "\n";*/
  return 0;
}
