#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iosfwd>
#include <string>
#include "doublelist.hpp"

namespace kovshikov
{
  using listPair = DoubleList< std::pair< std::string, DoubleList< size_t > > >;
  void createIntList(DoubleList< size_t > &list, std::string &integerString, bool &isBigNumber);
  void inputPairs(listPair &allPairs, bool &isBigNumber);
  void outputListName(const listPair &allPairs);
  void outputResult(const listPair &allPairs, const  bool &isBigNumber);
}

#endif
