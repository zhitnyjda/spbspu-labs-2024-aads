#include <iostream>
#include <cstddef>
#include "list.hpp"

int main()
{
  List<int> lst;
  lst.push_front(7);
  lst.push_front(11);
  for (int i = 0; i < lst.GetSize(); i++)
  {
    std::cout << lst[i] << endl;
  }
  std::cout << endl << "popBack " << endl << endl;
  lst.popBack();
  for (int i = 0; i < lst.GetSize(); i++)
  {
    std::cout << lst[i] << endl;
  }
  return 0;
}
