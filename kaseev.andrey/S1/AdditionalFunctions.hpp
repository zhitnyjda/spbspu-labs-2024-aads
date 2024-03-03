#ifndef ACID_ADDITIONALFUNCTIONS_HPP
#define ACID_ADDITIONALFUNCTIONS_HPP
#include "MaineArray.hpp"

namespace kaseev
{
  void readList(const std::string &line, kaseev::List<std::pair<std::string, kaseev::List<int>>>& arr);
  int sumNumbersInString(const std::string& line);
  int sumNumbersInArray(const kaseev::List<std::string> sums);
}

#endif
