#include <iostream>
#include <vector>
#include <string>
#include "list.hpp"

int main()
{
  sobolevsky::List< std::vector< long long > > list;

  std::string nodeName;
  std::string tempNodeName;
  std::cin >> tempNodeName;
  while (std::cin)
  {
    nodeName = tempNodeName;
    if (std::cin.eof())
    {
      sobolevsky::Iterator< std::vector< long long > > iter( list.head );
      std::cout << iter.name() << " ";
      list.clear();
      return 1;
    }
    std::vector< long long > vec;
    std::string elem;
    while (std::cin >> elem)
    {
      if (isalpha(elem[0]))
      {
        tempNodeName = elem;
        break;
      }
      long long i = stoll(elem);
      vec.push_back(i);
    }
    list.pushBack(vec, nodeName);
  }
  return 0;
}
