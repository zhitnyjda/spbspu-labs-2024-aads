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
  for (int i = 0; i < arr.size(); ++i) {
    std::pair<std::string, kaseev::List<int>> list = arr[i];
    std::cout << list.first << " ";
  }
  std::cout << "\n";
  bool finished = false;
  int index = 0;
  kaseev::List<std::pair<std::string, kaseev::List<int>>> sum;
  while (!finished) {
    finished = true;
    std::string currentString;
    for (int i = 0; i < arr.size(); ++i) {
      const std::pair<std::string, kaseev::List<int>>& list = arr[i];
      if (index < list.second.size()) {
        std::cout << list.second[i] << " ";
        currentString += std::to_string(list.second[i]) + " ";
        finished = false;
      }
    }
    if (!finished) {
      std::cout << "\n";
      sum.pushBack({currentString, kaseev::List<int>()});
    }
    index++;
  }
  kaseev::sumNumbersInArray(sum);
  return 0;
}
