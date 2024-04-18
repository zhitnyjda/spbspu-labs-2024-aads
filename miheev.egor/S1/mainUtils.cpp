#include "mainUtils.hpp"

namespace miheev
{
  std::pair<SI_pair*, size_t> expandArr(SI_pair* pairs, size_t size)
  {
      const size_t additionalSize = 5;
      SI_pair* copy = new SI_pair[size + additionalSize];
      for (size_t i = 0; i < size; i++)
      {
        copy[i] = pairs[i];
      }
      size += additionalSize;
      std::pair< SI_pair*, size_t > result(pairs, size);
      return result;
  }

  std::string takeWord(std::string& line)
  {
    size_t spaceIndex = line.find(' ');
    std::string word = line.substr(0, spaceIndex);
    line = spaceIndex == std::string::npos ? "" : line.substr(spaceIndex + 1);
    return word;
  }

  List< size_t > readNumbers(std::string numbers)
  {
    List< size_t > list;
    size_t curNum = 0;

    while (numbers.length() > 0)
    {
      try
      {
        curNum = std::stoull(takeWord(numbers));
      }
      catch(const std::invalid_argument& err)
      {
        return list;
      }
      list.pushBack(curNum);
    }

    return list;
  }

  SI_pair getSIPair(std::istream& stream)
  {
    SI_pair pair;
    std::string line = "";
    std::getline(stream, line);
    pair.first = takeWord(line);

    pair.second = readNumbers(line);
    return pair;
  }

  ListIter* getNonEmptyIters(SI_pair* pairs, size_t size)
  {
    ListIter* iters = new ListIter[size];
    for (size_t i = 0; i < size; i++)
    {
      if (!pairs[i].second.empty())
      {
        iters[i] = ListIter(pairs[i].second.begin());
      }
    }
    return iters;
  }

  List< size_t >* getLists(SI_pair* pairs, size_t size)
  {
    List< size_t >* lists = new List< size_t > [size];
    for (size_t i = 0; i < size; i++)
    {
      lists[i] = pairs[i].second;
    }
    return lists;
  }

  size_t maxListSize(List< size_t >* lists, size_t size)
  {
    size_t max = lists[0].size();
    for (size_t i = 0; i < size; i++)
    {
      List< size_t > list = lists[i];
      size_t size = list.size();
      if (size > max)
      {
        max = size;
      }
    }
    return max;
  }



}
