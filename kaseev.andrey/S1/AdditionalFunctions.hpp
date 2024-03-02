#ifndef ACID_ADDITIONALFUNCTIONS_HPP
#define ACID_ADDITIONALFUNCTIONS_HPP
#include "MaineArray.hpp"

namespace kaseev
{
  void readList(std::string &line, kaseev::List<std::pair<std::string, kaseev::List<int>>>& arr);
}

#endif
