#include <iostream>
#include "list.hpp"

int main()
{
  zheleznyakov::List<int> list;
  for (int i = 20; i > 0; i--)
  {
    if (i % 2 == 0)
    {
      list.pushBack(i);
    }
    else
    {
      list.pushFront(i);
    }
  }
  for (size_t i = 0; i < list.getSize(); i++)
  {
    std::cout << i << ' ' << list[i] << '\n';
  }
  return 0;
}
