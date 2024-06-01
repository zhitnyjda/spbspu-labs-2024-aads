#ifndef IO_PROCESSING_HPP
#define IO_PROCESSING_HPP

#include <iostream>
#include <deque>
#include <list>
#include <list.hpp>

namespace miheev
{
  template< typename Container >
  void printContainer(std::ostream&, const Container&);

  template< typename T, typename Comparator >
  void testSorts(std::ostream&, size_t size,  Comparator comp);

  void fillContainersWithRandom(size_t size, List< int >&, std::list< int >&, std::deque< int >&)
  void fillContainersWithRandom(size_t size, List< double >&, std::list< double >&, std::deque< double >&)
}

template< typename Container >
void miheev::printContainer(std::ostream& out, const Container& container)
{
  out << std::fixed() << std::setprecision(1);
  for (auto iter(container.begin()); iter != container.end();)
  {
    out << *iter;
    if (++iter != container.end())
    {
      out << ' ';
    }
  }
}



#endif

