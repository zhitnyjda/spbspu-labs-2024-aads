#include <iostream>
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

  while (!std::cin.eof())
  {
    if (unusedIndex >= pairsSize)
    {
      std::pair< SI_pair*, size_t > expanded = expandArr(pairs, pairsSize);
      SI_pair* temp = pairs;
      pairs = expanded.first;
      delete[] temp;
      pairsSize = expanded.second;
    }

    SI_pair pair = getSIPair(std::cin);
    if (pair.first != "")
    {
      pairs[unusedIndex++] = pair;
    }
  }

  if (unusedIndex <= 0)
  {
    delete[] pairs;
    std::cout << "0\n";
    return 0;
  }

  for (size_t i = 0; i < unusedIndex; i++)
  {
    std::cout << pairs[i].first;
    if (i < unusedIndex - 1)
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';

  ListIter* iters = getNonEmptyIters(pairs, unusedIndex);
  List< size_t >* lists = getLists(pairs, unusedIndex);
  size_t maxSize = maxListSize(lists, unusedIndex);
  delete[] lists;

  if (maxSize <= 0)
  {
    std::cout << "0\n";
    delete[] pairs;
    delete[] iters;
    return 0;
  }

  size_t* sumArr = new size_t[maxSize]{};
  size_t index = 0;
  bool isOverflow = false;

  bool flag = false;
  do
  {
    flag = false;
    bool isFirstToPrint = true;
    for (size_t i = 0; i < unusedIndex; i++)
    {
      ListIter iter = iters[i];
      if (iter != nullptr)
      {
        if (!isOverflow and std::numeric_limits<size_t>::max() - *iter >= sumArr[index])
        {
          sumArr[index] += *iter;
        }
        else
        {
          isOverflow = true;
        }
        if (iter)
        {
          flag = true;
        }
        if (!isFirstToPrint)
        {
          std::cout << ' ';
        }
        std::cout << *iter;
        isFirstToPrint = false;
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
    pPrint(sumArr, maxSize);
  }
  delete[] sumArr;

  if (isOverflow)
  {
    std::cerr << "sum is bigger than size_t can contain\n";
    return 1;
  }
  return 0;
}
