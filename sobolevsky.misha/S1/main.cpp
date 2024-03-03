#include <iostream>
#include <vector>
#include <string>
#include "list.hpp"

int main()
{
  sobolevsky::List< std::vector<int> > list;

  std::string nodeName;
  while (std::cin)
  {
    std::cin >> nodeName;
    if (std::cin.eof())
    {
      sobolevsky::Iterator< std::vector<int> > iter( list.head );
      std::cout << iter.name() << " ";
      list.clear();
      return 1;
    }
    std::vector<int> vec;
    std::string elem;
    std::string end = "\n";
    while (std::cin >> elem)
    {
      if (elem == end)
      {
        break;
      }
      int i = stoi(elem);
      vec.push_back(i);
    }
    list.pushBack(vec, nodeName);
  }
  return 0;
}
