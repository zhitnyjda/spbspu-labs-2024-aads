#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "list.hpp"

int main() {
  std::string line;
  std::list<std::pair<std::string, List<int>>> sequences;

  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string name;
    int num;
    if (!(iss >> name)) {
      std::cerr << "Error: Invalid input format" << std::endl;
      return 1;
    }
    List<int> numbers;
    while (iss >> num) {
     numbers.push_back(num);
    }
    sequences.emplace_back(name, numbers);
  }

  if (sequences.empty()) {
    std::cout << "0" << std::endl;
    return 0;
  }

  for (const auto& seq : sequences) {
    std::cout << seq.first << " ";
  }
  std::cout << std::endl;

  bool itemsRemaining;
  int col = 0;
  std::vector<int> sums;
  do {
    itemsRemaining = false;
    List<int> columnValues;
    for (auto& seq : sequences) {
      if (seq.second.size() > col) {
        auto it = std::next(seq.second.begin(), col);
        if (it != seq.second.end()) {
          columnValues.push_back(*it);
          itemsRemaining = true;
        }
      }
    }
    if (!columnValues.empty()) {
      int sum = 0;
      for (int val : columnValues) {
        std::cout << val << " ";
        sum += val;
      }
      sums.push_back(sum);
      std::cout << std::endl;
    }
    col++;
  } while (itemsRemaining);

  if (!sums.empty()) {
    for (int sum : sums) {
      std::cout << sum << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
