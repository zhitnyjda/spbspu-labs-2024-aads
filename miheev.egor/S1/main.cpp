#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include "list.hpp"
#include "mainUtils.hpp"


int main()
{
  using namespace miheev;

  size_t pairsSize = 5;
  SI_pair* pairs = new SI_pair[pairsSize];
  size_t unusedIndex = 0;

  while (1)
  {
    std::string line;
    std::getline(std::cin, line);

    if (std::cin.eof())
    {
      std::cout << "EOF\n";
      break;
    }
    std::istringstream stream(line);

    if (unusedIndex >= pairsSize)
    {
      const size_t additionalSize = 5;
      SI_pair* copy = new SI_pair[pairsSize + additionalSize];
      for (size_t i = 0; i < pairsSize; i++)
      {
        copy[i] = pairs[i];
      }
      pairsSize += additionalSize;
      delete [] pairs;
      pairs = copy;
    }
    pairs[unusedIndex++] = getSIPair(stream);
  }

  for (size_t i = 0; i < unusedIndex; i++)
  {
    std::cout << pairs[i].first << ' ';
  }
  std::cout << '\n';

  ListIter* iters = getIters(pairs, unusedIndex);
  List< int >* lists = getLists(pairs, unusedIndex);

  int maxSize = maxListSize(lists, unusedIndex);
  int* sumArr = new int[maxSize]{};
  size_t index = 0;

  bool flag = false;
  do
  {
    flag = false;
    for (size_t i = 0; i < unusedIndex; i++)
    {
      ListIter iter = iters[i];
      if (iter != nullptr and !iter.isEmptyObject())
      {
        sumArr[index] += *iter;
        std::cout << *iter << ' ';
        if (iter)
        {
          flag = true;
        }
        iters[i] = ++iter;
      }
    }
    index++;
    std::cout << '\n';
  } while (flag);

  for (size_t i = 0; i < maxSize; i++)
  {
    std::cout << sumArr[i] << ' ';
  }
  std::cout << '\n';

  delete[] pairs;
  return 0;
}
