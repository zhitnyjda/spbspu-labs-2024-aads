
#include <iostream>
#include "doublelist.hpp"

using namespace kovshikov;
int main()
{
  std::cout << "start checking DoubleList" << "\n";
  DoubleList<int> list;
  list.pushFront(7);
  std::cout << "add front 7" << ": " << list.front() << "\n";
  list.pushFront(9);
  std::cout << "add front 9" << ": " << list.front() << "\n";

  return 0;
}
