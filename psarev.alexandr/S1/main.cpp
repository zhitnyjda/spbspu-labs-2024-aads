#include <iostream>
#include "list.hpp"

int main()
{
  psarev::List<int> list;
  list.pushBack(20);
  list.pushFront(21);

  for (size_t i = 0; i < list.getSize(); i++)
  {
    std::cout << list[i] << ' ';
  }
  std::cout << '\n';
}
