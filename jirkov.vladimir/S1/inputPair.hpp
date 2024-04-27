#ifndef INPUT_PAIR_HPP
#define INPUT_PAIR_HPP
#include "list.hpp"
#include <string>
#include <iostream>

namespace jirkov
{
  List<std::pair<std::string, List<size_t>>> inputPair(std::istream& input);
}

#endif
