#ifndef OUTPUTFUNCTIONS_HPP
#define OUTPUTFUNCTIONS_HPP
#include <ostream>

namespace redko
{
  template< typename It >
  void printSorted(std::ostream & out, It first, It last)
  {
    while (first != last)
    {
      out << *first;
      out << (++first == last ? '\n' : ' ');
    }
  }
}

#endif
