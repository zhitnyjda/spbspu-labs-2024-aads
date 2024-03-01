#include <iostream>
#include <cstddef>
#include "list.hpp"

int main()
{
  List<int> lst;

  bool empty = lst.is_empty();
  lst.push_back(3);
  lst.push_back(6);
  lst.push_back(10);
  lst.push_front(4);
  lst.push_front(3);
  lst.push_front(4);
  auto it_begin = lst.begin();
  auto it_end = lst.end();
  std::cout << *it_begin;
  it_begin++;
  bool b = it_begin == it_end;
  std::cout << b;
  std::cout << *it_begin;
  lst.pop_back();
  lst.pop_back();
  lst.clear();
  return 0;
}
