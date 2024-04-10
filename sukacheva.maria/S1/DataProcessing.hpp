#ifndef DATAPROCESSING_HPP
#define DATAPROCESSING_HPP

#include <iostream>
#include "List.hpp"

namespace sukacheva {
  using listOfPairs = List< std::pair< std::string, List< size_t > > >;
  listOfPairs listInput(std::istream& in);
  size_t maxListSize(listOfPairs& newList);
  void printNameList(listOfPairs& newList);
  void printArgs(listOfPairs& newList);
}

#endif
