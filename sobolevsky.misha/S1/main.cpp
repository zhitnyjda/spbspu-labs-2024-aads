#include <iostream>
#include <vector>
#include "list.hpp"

int main()
{
  sobolevsky::List< int > list;
  list.pushBack(2);
  list.pushBack(56);
  list.pushBack(7);

  sobolevsky::Iterator< int > iter( list.head );

  std::cout << *iter << "\n";

  return 0;
}
