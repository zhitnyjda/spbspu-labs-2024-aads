#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include "list.hpp"
namespace jirkov
{
  void printListNames(const List<std::pair<std::string, List<size_t>>>& list);
  void printValues(const List<std::pair<std::string, List<size_t>>>& list, size_t maxSize, List<size_t>& sums);
  void printSums(List<size_t>& sums);
  void checkForOverflow(size_t sum, size_t value);
}

#endif
