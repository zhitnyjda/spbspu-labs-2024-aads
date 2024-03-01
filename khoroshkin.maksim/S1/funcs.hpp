#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <iostream>
#include "list.hpp"

namespace khoroshkin
{
  void printResult(std::ostream & out, List< std::pair< std::string, List< int > > > & allPairs, size_t maxLength);
  template < typename T >
  bool checkAllNext(int index, ListIterator< T > it, List< std::pair< std::string, List< int > > > & allPairs);
}

#endif
