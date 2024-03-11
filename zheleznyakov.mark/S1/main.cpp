#include <iostream>
#include <string>
#include "list.hpp"
#include "numbers.hpp"

int main()
{
  zheleznyakov::List<std::pair<std::string, zheleznyakov::List<unsigned long long>>> pairs;
  size_t maxSequenceSize = 0;
  size_t pairsCount = -1;
  std::string input;
  while (std::cin >> input)
  {
    if (zheleznyakov::isNumeric(input))
    {
      pairs[pairsCount].second.pushBack(std::stoull(input));
    }
    else
    {
      pairs.pushBack({input, {}});
      pairsCount++;
    }
  }
  return 0;
}
