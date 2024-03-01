#include <iostream>
#include <vector>
#include "list.hpp"

int main()
{
  List< int > list;
  list.pushBack(2);
  list.pushBack(56);
  list.pushBack(7);

  list.clear();
  return 0;
}
