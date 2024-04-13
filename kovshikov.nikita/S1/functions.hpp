#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iosfwd>
#include <string>
#include "doublelist.hpp"

namespace kovshikov
{
  void createIntList(DoubleList< size_t > &list, std::string &integerString, bool &isBigNumber);
  void inputPairs(DoubleList< std::pair< std::string, DoubleList< size_t > > > &allPairs, bool &isBigNumber);
  void outputListName(const DoubleList< std::pair< std::string, DoubleList< size_t > > > &allPairs);
  void outputResult(const DoubleList< std::pair< std::string, DoubleList< size_t > > > &allPairs, const  bool &isBigNumber);
}

#endif
