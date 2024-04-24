#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include "list.hpp"
namespace jirkov
{
  void printListNames(const List<std::pair<std::string, List<size_t>>>& list);
  void printRowValues(const List<std::pair<std::string, List<size_t>>>& list, size_t index, size_t& sum, bool& overflowError);

}

#endif
