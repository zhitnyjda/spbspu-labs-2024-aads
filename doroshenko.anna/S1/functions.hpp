#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "list.hpp"
#include <string>
#include <iostream>

namespace doroshenko
{
  List< std::pair< std::string, List< size_t > > > listInput(std::istream& input);
  size_t getMaxSize(List< std::pair< std::string, List< size_t > > >& list);
  void namesOutput(doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > list, std::ostream& output);
  void listOutput(doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > list, std::ostream& output, doroshenko::List< size_t >& sums);
  void sumsOutput(doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > list, std::ostream& output, doroshenko::List< size_t >& sums);
}

#endif
