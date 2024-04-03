#ifndef ACID_ADDITIONALFUNCTIONS_HPP
#define ACID_ADDITIONALFUNCTIONS_HPP
#include "MaineArray.hpp"

namespace kaseev
{
  int readList(const std::string &line, kaseev::List<std::pair<std::string, kaseev::List<unsigned long long>>>& arr, bool &marker);
  int sumNumbersInString(const std::string& line);
  void sumNumbersInArray(const kaseev::List<std::pair<std::string, kaseev::List<int>>>& sums, bool &marker);
  void printListNames(const kaseev::List<std::pair<std::string, kaseev::List<unsigned long long>>>& arr);
  kaseev::List<std::pair<std::string, kaseev::List<int>>>
  calculateSumList(const kaseev::List<std::pair<std::string, kaseev::List<unsigned long long>>>& arr);
}

#endif
