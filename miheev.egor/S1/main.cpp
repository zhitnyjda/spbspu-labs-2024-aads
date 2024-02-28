#include <iostream>
#include <utility>
#include <string>
#include "list.hpp"
#include "utils.hpp"

int main()
{
  using namespace miheev;
  using SI_pair = std::pair< std::string, List< int > >;

  size_t pairsSize = 5;
  SI_pair* pairs = new SI_pair[pairsSize];
  size_t unusedIndex = 0;

  SI_pair curPair;
  std::string word;
  int number = 0;
  while (!std::cin.eof())
  {
    std::cin >> word;
    std::cout << word << '\n';
    curPair.first = word;

    size_t index = 0;
    while (std::cin)
    {
      std::cin >> number;
      std::cout << number << '\n';
      if (index == 0)
      {
        curPair.second = List< int >(number);
      }
      else
      {
        curPair.second.pushBack(number);
      }
      index++;
    }
    if (unusedIndex == pairsSize)
    {
      copyWithExpand(pairs, pairsSize);
    }
    pairs[unusedIndex] = curPair;
    unusedIndex++;
  }

  return 0;
}

