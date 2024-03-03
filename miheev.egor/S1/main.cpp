#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include "list.hpp"

using SI_pair = std::pair< std::string, miheev::List< int > >;
using ListIter = miheev::List<int>::Iterator;

namespace miheev
{
  void expandPairsArr(SI_pair*& pairs, size_t& size)
  {
    const size_t additionalSize = 5;
    SI_pair* copy = new SI_pair[size + additionalSize];
    for (size_t i = 0; i < size; i++)
    {
      copy[i] = pairs[i];
    }
    size += additionalSize;
    delete [] pairs;
    pairs = copy;
  }

  miheev::List< int > readNumbers(std::istream& stream)
  {
    if ((stream >> std::ws).eof())
    {
      List< int > list;
      return list;
    }

    int number = 0;
    stream >> number;
    List< int > list(number);

    while(stream >> number)
    {
      list.pushBack(number);
    }
    list.print();
    return list;
  }

  SI_pair getSIPair(std::istream& stream)
  {
    SI_pair pair;
    stream >> pair.first; // reading word
    pair.second = readNumbers(stream);
    return pair;
  }

  ListIter* getIters(SI_pair* pairs, size_t size)
  {
    ListIter* iters = new ListIter[size];
    for (size_t i = 0; i < size; i++)
    {
      iters[i] = ListIter(pairs[i].second.begin());
    }
    return iters;
  }
}

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
      expandPairsArr(pairs, pairsSize);
    }
    pairs[unusedIndex++] = getSIPair(stream);
  }

  // print names
  for (size_t i = 0; i < unusedIndex; i++)
  {
    std::cout << pairs[i].first << ' ';
  }
  std::cout << '\n';

  ListIter* iters = getIters(pairs, unusedIndex);

  bool flag = false;
  do
  {
    flag = false;
    for (size_t i = 0; i < unusedIndex; i++)
    {
      ListIter iter = iters[i];
      if (iter != nullptr and !iter.isEmptyObject())
      {
        std::cout << *iter << ' ';
        if (iter)
        {
          flag = true;
        }
        iters[i] = ++iter;
      }
    }
    std::cout << '\n';
  } while (flag);

  delete[] pairs;
  return 0;
}

