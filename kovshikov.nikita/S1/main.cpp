#include <iostream>
#include "doublelist.hpp"
#include <utility>

using namespace kovshikov;
int main()
{
  std::cout << "start checking DoubleList" << "\n";
  DoubleList<int> list(5, 52);
  std::cout << list.front() << " " << list.back() << "\n";
  return 0;
}
