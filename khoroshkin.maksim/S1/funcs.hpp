#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <iostream>
#include <limits>
#include <stdexcept>
#include "list.hpp"

namespace khoroshkin
{
  template < typename T >
  void printResult(std::ostream & out, List< std::pair< std::string, List< T > > > & allPairs, int maxLength, bool isOverflow);
  template < typename T >
  bool checkAllNext(int index, ListIterator< T > it, List< T > & allPairs);
}

using namespace khoroshkin;

template < typename T >
void khoroshkin::printResult(std::ostream & out, List< std::pair< std::string, List< T > > > & allPairs, int maxLength, bool isOverflow)
{
  using type = std::pair<std::string, khoroshkin::List< T > >;
  if (allPairs.getSize() == 0)
  {
    throw std::logic_error("Empty list");
  }

  for (auto it = allPairs.begin(); it != allPairs.end(); ++it)
  {
    out << (*it).first;
    allPairs.next(it) == allPairs.end() ? std::cout << "\n" : std::cout << " ";
  }

  if (allPairs[0].second.isEmpty())
  {
    throw std::logic_error("Empty list");
  }

  for (int i = 0; i < maxLength; i++)
  {
    for (auto it = allPairs.begin(); it != allPairs.end(); it++)
    {
      if ((*it).second.getSize() > i)
      {
        out << (*it).second[i];
        (allPairs.next(it) == allPairs.end() || !checkAllNext< type >(i, it, allPairs)) ? out << "\n" : out << " ";
      }
    }
  }

  for (int i = 0; i < maxLength; i++)
  {
    long long sum = 0;
    for (auto it = allPairs.begin(); it != allPairs.end(); it++)
    {
      if ((*it).second.getSize() > i)
      {
        if (std::numeric_limits<long long>::max() - sum < (*it).second[i] || isOverflow)
        {
          throw std::overflow_error("overflow!");
        }
        sum += (*it).second[i];
      }
    }
    out << sum;
    (i + 1 == maxLength) ? out << "\n" : out << " ";
  }
}

template < typename T>
bool khoroshkin::checkAllNext(int index, ListIterator< T > it, List< T > & allPairs)
{
  bool flag = false;
  while (allPairs.next(it) != allPairs.end())
  {
    if ((*allPairs.next(it)).second.getSize() - 1 >= index)
    {
      flag = true;
    }
    ++it;
  }
  return flag;
}

#endif
