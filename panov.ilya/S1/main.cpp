#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "list.hpp"

int main() {
  Panov::List<std::pair<std::string, std::vector<unsigned long long int>>> sequences;

  bool hasOverflow = false;
  std::string line;
  bool isEmpty = true;
  while (std::getline(std::cin, line)) {
    if (line.empty()) break;
    isEmpty = false;

    std::vector<std::string> inputLines;
    inputLines.push_back(line);

    for (const auto& input : inputLines) {
      std::istringstream iss(input);
      std::string name;
      iss >> name;

      std::vector<unsigned long long int> sequence;
      unsigned long long int num;
      while (iss >> num) {
        const unsigned long long int overflowThreshold = std::numeric_limits<unsigned long long int>::max() - 5;
        if (num >= overflowThreshold) {
          hasOverflow = true;
          break;
        }
        sequence.push_back(num);
      }

      sequences.push_back({ name, sequence });

      if (hasOverflow) {
        std::cerr << "Formed lists with exit code 1 and error message in standard error because of overflow" << std::endl;
        return 1;
      }
    }
  }

  if (isEmpty) {
    char symbol;
    std::cin >> symbol;
    std::cout << symbol << std::endl;
    std::cout << 0 << std::endl;
  }

  for (const auto& seq : sequences) {
    std::cout << seq.first << " ";
  }
  std::cout << std::endl;

  size_t maxLength = 0;
  for (const auto& seq : sequences)
    maxLength = std::max(maxLength, seq.second.size());

  for (size_t i = 0; i < maxLength; ++i) {
    for (const auto& seq : sequences) {
      if (i < seq.second.size()) {
        std::cout << seq.second[i] << " ";
      }
    }
    std::cout << std::endl;
  }

  for (size_t i = 0; i < maxLength; ++i) {
    unsigned long long int sum = 0;
    for (const auto& seq : sequences) {
      if (i < seq.second.size()) {
        sum += seq.second[i];
      }
    }
    std::cout << sum << " ";
  }
  std::cout << std::endl;

  return 0;
}
