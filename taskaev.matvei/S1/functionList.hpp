#ifndef FUNCTIONLIST_HPP
#define FUNCTIONLIST_HPP
#include "List.hpp"
#include <limits>
#include <iostream>
#include <cstddef>
#include <string>

namespace taskaev
{
  using list_t = List< std::pair< std::string, List< size_t > > >;
  using sums_t = List< size_t >;
  list_t inputList(std::istream& input, list_t& list)
  {
    std::string name = "";
    input >> name;
    while (input)
    {
      list.pushFront({ name, List<size_t>() });
      while (input >> name && !std::isalpha(name[0]))
      {
        list.front().second.pushBack(std::stoull(name));
      }
    }
    return list;
  }
  void outputListName(list_t& list, std::ostream& output)
  {
    list.reverse();
    list_t::Iterator iterator = list.begin();
    while (iterator != list.end())
    {
      output << iterator->first;
      if (++iterator != list.end())
      {
        output << " ";
      }
    }
  }

  void outputList(list_t& list, sums_t& sums, std::ostream& output)
  {
    size_t maxNum = 1;
    list_t::Iterator iterator = list.begin();
    while (iterator != list.end())
    {
      size_t j = 0;
      auto it = iterator->second.begin();
      while (it != iterator->second.end())
      {
        j++;
        maxNum = (maxNum > j) ? maxNum : j;
        it++;
      }
      iterator++;
    }
    if (maxNum != 1)
    {
      output << "\n";
    }
    bool flag = false;
    size_t sum;
    size_t j = 0;
    const size_t maxLimit = std::numeric_limits< size_t >::max();
    while (j < maxNum)
    {
      j++;
      sum = 0;
      iterator = list.begin();
      while (iterator != list.end())
      {
        if (!iterator->second.isEmpty())
        {
          if (sum > 0 || flag)
          {
            output << " ";
          }
          if (maxLimit - sum >= iterator->second.front())
          {
            sum += iterator->second.front();
          }
          else
          {
            flag = true;
          }
          output << iterator->second.front();
          iterator->second.popFront();
        }
        iterator++;
      }
      output << "\n";
      sums.pushFront(sum);
      if (flag)
      {
        throw std::overflow_error("Stack overflow SOS!!!");
      }
    }
  }

  void outputSum(sums_t& sums, std::ostream& output)
  {
    sums.reverse();
    sums_t::Iterator iteratorSums = sums.begin();
    if (!sums.isEmpty())
    {
      while (iteratorSums != sums.end())
      {
        output << *iteratorSums;
        if (++iteratorSums != sums.end())
        {
          output << " ";
        }
      }
      output << "\n";
    }
    else
    {
      output << "0\n";
    }
  }
}

#endif
