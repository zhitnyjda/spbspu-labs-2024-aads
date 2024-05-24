#include <iostream>
#include <list>
#include <forward_list>
#include "sorts.hpp"

int main()
{
  using namespace miheev;
  std::list< int > l({15, 13, 1, 32, 3});
  shellSort(l.begin(), l.end(), std::less< int >());

  return 0;
}