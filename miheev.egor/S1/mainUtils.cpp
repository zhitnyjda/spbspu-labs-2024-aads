#include "mainUtils.hpp"

namespace miheev
{
  List< int > readNumbers(std::istream& stream)
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

  List< int >* getLists(SI_pair* pairs, size_t size)
  {
    List< int >* lists = new List< int > [size];
    for (size_t i = 0; i < size; i++)
    {
      lists[i] = pairs[i].second;
    }
    return lists;
  }
  size_t maxListSize(List< int >* lists, size_t size)
  {
    int max = lists[0].size();
    for (size_t i = 0; i < size; i++)
    {
      List< int > list = lists[i];
      int size = list.size();
      if (size > max)
      {
        max = size;
      }
    }
    return max;
  }
}