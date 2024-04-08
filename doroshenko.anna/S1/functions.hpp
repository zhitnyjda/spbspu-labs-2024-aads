#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>
#include <iostream>
#include <limits>
#include "list.hpp"


namespace doroshenko
{
  using this_t = List< std::pair< std::string, List< size_t > > >;

  size_t getMaxSize(this_t& list)
  {
    size_t size = 0;
    size_t maxSize = 0;
    this_t::Iterator iterator = list.begin();
    while (iterator != this_t::ConstIterator())
    {
      size = iterator->second.getSize();
      maxSize = size > maxSize ? size : maxSize;
      iterator++;
    }
    return maxSize;
  }

  this_t listInput(std::istream& input)
  {
    std::string inputString = "";
    this_t inputList;
    unsigned long long readNumber = 0;
    const size_t maximum = std::numeric_limits< size_t >::max();
    while (input >> inputString)
    {
      if (std::isalpha(inputString[0]))
      {
        inputList.pushBack({ inputString, List< size_t >() });
      }
      else
      {
        readNumber = std::stoull(inputString);
        if (readNumber > maximum)
        {
          throw std::overflow_error("overflow error");
        }
        else
        {
          inputList.back().second.pushBack(readNumber);
        }
      }
    }
    return inputList;
  }

  void namesOutput(this_t& list, std::ostream& output)
  {
    this_t::Iterator iterator = list.begin();
    if (!list.isEmpty())
    {
      while (iterator != list.end())
      {
        if (iterator != list.begin())
        {
          output << " ";
        }
        output << iterator->first;
        iterator++;
      }
      output << "\n";
    }
    else
    {
      output << 0 << "\n";
    }
  }

  void listOutput(this_t& list, std::ostream& output, List< size_t >& sums)
  {
    this_t::Iterator iterator;
    size_t maxSize = getMaxSize(list);
    List< size_t >::Iterator localIterator = List< size_t >::ConstIterator();
    const size_t maximum = std::numeric_limits< size_t >::max();
    size_t sum = 0;
    bool overflowError = false;
    if (!list.isEmpty())
    {
      for (size_t index = 0; index < maxSize; index++)
      {
        iterator = list.begin();
        while (iterator != list.end())
        {
          if (iterator->second[index] != nullptr)
          {
            if (sum > 0)
            {
              output << " ";
            }
            localIterator = List< size_t >::ConstIterator(iterator->second[index]);
            std::cout << *localIterator;
            if (maximum - sum < *localIterator)
            {
              overflowError = true;
              output << "\n";
              throw std::overflow_error("overflow error");
            }
            else
            {
              sum = sum + *localIterator;
            }
          }
          iterator++;
        }
        if (!overflowError)
        {
          sums.pushBack(sum);
        }
        sum = 0;
        overflowError = false;
        output << "\n";
      }
    }
  }

  void sumsOutput(this_t& list, std::ostream& output, List< size_t >& sums)
  {
    List< size_t >::Iterator iteratorForSums = sums.begin();
    if (sums.isEmpty())
    {
      output << 0;
    }
    else
    {
      while (iteratorForSums != sums.end())
      {
        if (iteratorForSums != List< size_t >::ConstIterator())
        {
          if (iteratorForSums != sums.begin())
          {
            output << " ";
          }
          output << *iteratorForSums;
        }
        iteratorForSums++;
      }
    }
    output << "\n";
  }
}

#endif
