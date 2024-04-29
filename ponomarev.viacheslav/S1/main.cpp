#include "list.hpp"
#include "functions.hpp"
#include <iostream>
#include <utility>

int main()
{
  using pairs = ponomarev::List< std::pair< std::string, ponomarev::List< unsigned long long > > >;
  pairs data;
  pairs::Iterator iterator;
  std::string line = "";

  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string name = ponomarev::getName(line);
      data.pushBack(std::pair< std::string, ponomarev::List< unsigned long long > >(name, ponomarev::List< unsigned long long >()));
      iterator = data.begin();
      while (!line.empty())
      {
        unsigned long long num = ponomarev::getNumber(line);
        iterator->second.pushBack(num);
      }
    }
  }
  return 0;
}
