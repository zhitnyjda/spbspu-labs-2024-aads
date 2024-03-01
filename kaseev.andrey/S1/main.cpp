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
    kaseev::readList(line, arr);
  }

  for (size_t i = 0; i < arr.size(); ++i) {
    std::pair<std::string, kaseev::List<int>> list = arr[i];
    std::cout << list.first << " ";
  }
  std::cout << "\n";

  if (arr.empty()) {
    std::cout << "0 \n";
    return 1;
  }

  bool finished = false;
  size_t index = 0;
  kaseev::List<int> sum;

  while (!finished) {
    finished = true;
    for (size_t i = 0; i < arr.size(); ++i) {
      std::pair<std::string, kaseev::List<int>> list = arr[i];
      if (index < list.second.size()) {
        std::cout << list.second[index] << " ";
        sum.pushBack(list.second[index]);
        finished = false;
      }
    }
    if (!finished) {
      std::cout << "\n";
    }
    index++;
  }

  for (size_t i = 0; i <= sum.size() - 2; i++) {
    std::cout << sum[i] << " ";
  }
  std::cout << "\n";
  return 0;
}



/*
first 1 1 1
second 2 2 2 2
third
fourth 4 4
*/