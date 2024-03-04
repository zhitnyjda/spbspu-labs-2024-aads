#ifndef READINPUT_HPP
#define READINPUT_HPP
#include <iostream>
#include "list.hpp"

namespace hohlova
{
  List<std::pair<std::string, List<size_t>>>inputArr(std::istream& input);
}

#endif
