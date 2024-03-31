#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "list.hpp"

int main() {
  Panov::List<std::pair<std::string, std::vector<unsigned long long>>> sequences;

  std::vector<std::string> inputLines;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) break;
    inputLines.push_back(line);
  }

  bool hasOverflow = false;
  for (const auto& input : inputLines) {
    std::istringstream iss(input);
    std::string name;
    iss >> name;

    std::vector<unsigned long long> sequence;
    unsigned long long num;
    while (iss >> num) {
      if (num == std::numeric_limits<unsigned long long>::max()) {
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

  if (inputLines.empty()) {
    std::cout << "Zero exit code without error message in standard error and 0 on separate line as output" << std::endl;
    return 0;
  }

  for (size_t i = 0; i < inputLines.size(); ++i) {
    if (i != 0) std::cout << ' ';
    std::istringstream iss(inputLines[i]);
    std::string name;
    iss >> name;
    std::cout << name;
  }
  std::cout << std::endl;

  size_t maxLength = 0;
  for (const auto& seq : sequences)
    maxLength = std::max(maxLength, seq.second.size());

  for (size_t i = 0; i < maxLength; ++i) {
    bool firstElement = true;
    for (const auto& seq : sequences) {
      if (i < seq.second.size()) {
        if (!firstElement)
          std::cout << ' ';
        else
          firstElement = false;
        std::cout << seq.second[i];
      }
    }
    std::cout << std::endl;
  }

  for (size_t i = 0; i < maxLength; ++i) {
    unsigned long long sum = 0;
    for (const auto& seq : sequences) {
      if (i < seq.second.size()) {
        sum += seq.second[i];
      }
    }
    std::cout << sum;
    if (i != maxLength - 1)
      std::cout << ' ';
  }
  std::cout << std::endl;

  return 0;
}
