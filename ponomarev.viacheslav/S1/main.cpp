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
  size_t dataSize = 0;
  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string name = ponomarev::getName(line);
      std::pair< std::string, ponomarev::List< unsigned long long > > pair = { name, {} };
      data.pushBack(pair);
      iterator = data.begin();
      dataSize += 1;
      for (size_t i = 0; i < (dataSize - 1); i++)
      {
        iterator++;
      }
      while (!line.empty())
      {
        unsigned long long num = ponomarev::getNumber(line);
        iterator->second.pushBack(num);
      }
    }
  }
  if (data.isEmpty())
  {
    std::cout << 0 << '\n';
  }
  else
  {
    iterator = data.begin();
    while (iterator != data.end())
    {
      std::cout << iterator->first;
      iterator++;
      std::cout << (iterator == data.end() ? '\n' : ' ');
    }
  }
  return 0;
}
