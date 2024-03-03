#ifndef MAIN_UTILS_HPP
#define MAIN_UTILS_HPP

#include "list.hpp"

using SI_pair = std::pair< std::string, miheev::List< int > >;
using ListIter = miheev::List<int>::Iterator;

namespace miheev
{
  void expandPairsArr(SI_pair*& pairs, size_t& size);
  List< int > readNumbers(std::istream& stream);
  SI_pair getSIPair(std::istream& stream);
  ListIter* getIters(SI_pair* pairs, size_t size);
  List< int >* getLists(SI_pair* pairs, size_t size);
  size_t maxListSize(List< int >* lists, size_t size);
}

#endif
