#include <iostream>
#include <sstream>
#include <utility>
#include <limits>
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
  if (unusedIndex > 0)
  {
    std::cout << '\n';
  }

  ListIter* iters = getIters(pairs, unusedIndex);

  List< size_t >* lists = getLists(pairs, unusedIndex);
  size_t maxSize = maxListSize(lists, unusedIndex);
  delete[] lists;

  size_t* sumArr = new size_t[maxSize]{};
  size_t index = 0;
  bool isOverflow = false;

  bool flag = false;
  do
  {
    flag = false;
    for (size_t i = 0; i < unusedIndex; i++)
    {
      ListIter iter = iters[i];
      if (iter != nullptr and !iter.isEmptyObject())
      {
        if (!isOverflow and std::numeric_limits<size_t>::max() - *iter >= sumArr[index])
        {
          sumArr[index] += *iter;
        }
        else
        {
          isOverflow = true;
        }
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

  delete[] iters;
  delete[] pairs;

  if (!isOverflow)
  {
    for (size_t i = 0; i < maxSize; i++)
    {
      std::cout << sumArr[i];
      if (i < maxSize - 1)
      {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
  delete[] sumArr;

  if (isOverflow)
  {
    std::cerr << "sum is bigger than size_t can contain\n";
    return 1;
  }
  return 0;
}
