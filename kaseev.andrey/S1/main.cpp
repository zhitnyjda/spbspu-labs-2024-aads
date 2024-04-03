#include <iostream>
#include <string>
#include "MaineArray.hpp"
#include "AdditionalFunctions.hpp"

int main() {
  kaseev::List<std::pair<std::string, kaseev::List<int>>> arr;
  std::string line;
  bool marker = false;
  while (std::getline(std::cin, line)) {
    if (line.empty())
    {
      break;
    }
    marker = kaseev::readList(line, arr, marker);
  }

  kaseev::printListNames(arr);
  kaseev::List<std::pair<std::string, kaseev::List<int>>> sum = kaseev::calculateSumList(arr);
  if (marker)
  {
    std::cerr << "overflow\n";
    return 1;
  }
  kaseev::sumNumbersInArray(sum, marker);
  return 0;
}
