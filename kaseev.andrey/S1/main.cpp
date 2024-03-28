#include <iostream>
#include <string>
#include "MaineArray.hpp"
#include "AdditionalFunctions.hpp"

int main() {
  kaseev::List<std::pair<std::string, kaseev::List<int>>> arr;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty())
    {
      break;
    }
    int marker = kaseev::readList(line, arr);
    if (marker == 1)
    {
      return 1;
    }
  }
  if (arr.empty()) {
    std::cout << "0\n";
    return 0;
  }
  kaseev::printListNames(arr);
  kaseev::List<std::pair<std::string, kaseev::List<int>>> sum;
  kaseev::calculateSumList(sum, arr);
  kaseev::sumNumbersInArray(sum);
  return 0;
}
