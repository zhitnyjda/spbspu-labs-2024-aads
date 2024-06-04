#include <iostream>
#include "sort.hpp"

int main()
{
  using namespace doroshenko;
  List<int> list;
  list.pushBack(3);
  list.pushBack(2);
  list.pushBack(1);
  list.pushBack(4);
  list.pushBack(5);
  mergeSort(list.begin(), list.end(), std::less<int>());
  List<int>::Iterator it = list.begin();
  while (it != list.end())
  {
    std::cout << *it;
    it++;
  }
  return 0;
}
