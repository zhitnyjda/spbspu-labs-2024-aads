#include <iostream>
#include <vector>
#include "list.hpp"

int main()
{
  sobolevsky::List< int > list;
  list.pushFront(2);
  list.pushFront(56);
  list.pushFront(7);

  sobolevsky::Iterator< int > iter( list.head );

  std::cout << *iter << "\n";

  return 0;
}
