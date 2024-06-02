#ifndef IO_PROCESSING_HPP
#define IO_PROCESSING_HPP

#include <iostream>
#include <iomanip>
#include <deque>
#include <list>
#include <list.hpp>

namespace miheev
{
  template< typename Container >
  void printContainer(std::ostream&, const Container&);

  void fillContainersWithRandom(size_t size, List< int >&, std::list< int >&, std::deque< int >&);
  void fillContainersWithRandom(std::deque< int >&, std::list< int >&, List< int >&, size_t amount);
  
  template< typename T, typename Comparator >
  void testSorts(std::ostream&, size_t size,  Comparator comp);
}

template< typename Container >
void miheev::printContainer(std::ostream& out, const Container& container)
{
  out << std::fixed << std::setprecision(1);
  for (auto iter(container.begin()); iter != container.end();)
  {
    out << *iter;
    if (++iter != container.end())
    {
      out << ' ';
    }
  }
}

void miheev::fillContainersWithRandom(std::deque< int >& deque, std::list< int >& bidirect, List< int >& forward, size_t amount)
{
  for (size_t i = 0; i < amount; i++)
  {
    int random = rand() % 100;
    deque.push_back(random);
  }
  std::copy(deque.begin(), deque.end(), std::back_inserter(forward));
  std::copy(deque.begin(), deque.end(), std::back_inserter(bidirect));
}

#endif

