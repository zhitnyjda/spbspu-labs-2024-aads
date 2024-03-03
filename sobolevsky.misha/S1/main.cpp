#include <iostream>
#include <vector>
#include <string>
#include "list.hpp"

int main()
{
  sobolevsky::List< std::vector<int> > list;

  std::string nodeName;
  std::string tempNodeName;
  std::cin >> tempNodeName;
  while (std::cin)
  {
    nodeName = tempNodeName;
    if (std::cin.eof())
    {
      sobolevsky::Iterator< std::vector<int> > iter( list.head );
      std::cout << iter.name() << " ";
      list.clear();
      return 1;
    }
    std::vector<int> vec;
    std::string elem;
    while (std::cin >> elem)
    {
      if (isalpha(elem[0]))
      {
        tempNodeName = elem;
        break;
      }
      int i = stoi(elem);
      vec.push_back(i);
    }
    list.pushBack(vec, nodeName);
  }
  return 0;
}
