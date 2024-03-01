#include <iostream>
#include "list.hpp"

int main()
{
  psarev::List<int> list;
  list.pushBack(20);
  list.pushBack(21);
  list.pushBack(22);
  list.pushBack(23);
  list.pushBack(24);
  for (size_t i = 0; i < list.getSize(); i++)
  {
    std::cout << list[i] << ' ';
  }
  std::cout << '\n';

  list.remove(2);
  for (size_t i = 0; i < list.getSize(); i++)
  {
    std::cout << list[i] << ' ';
  }
  std::cout << '\n';
}
