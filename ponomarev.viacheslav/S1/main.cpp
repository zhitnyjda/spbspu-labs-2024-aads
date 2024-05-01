#include <iostream>
#include <utility>
#include "functions.hpp"
#include "outputFunctions.hpp"
#include <algorithm>

int main()
{
  using pairs = ponomarev::List< std::pair< std::string, ponomarev::List< unsigned long long > > >;
  pairs data;
  pairs::Iterator iterator;
  std::string line = "";
  size_t maxLenSeq = 0;

  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string name = ponomarev::getName(line);
      std::pair< std::string, ponomarev::List< unsigned long long > > pair = { name, {} };
      data.pushBack(pair);
      iterator = data.begin();
      for (size_t i = 0; i < (data.getSize() - 1); i++)
      {
        iterator++;
      }
      size_t temp = 0;
      while (!line.empty())
      {
        unsigned long long num = ponomarev::getNumber(line);
        iterator->second.pushBack(num);
        temp++;
      }
      maxLenSeq = std::max(maxLenSeq, temp);
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
  ponomarev::List< unsigned long long > sums = ponomarev::outputNums< unsigned long long >(data, maxLenSeq);
  try
  {
    ponomarev::outputSums< unsigned long long >(sums);
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
