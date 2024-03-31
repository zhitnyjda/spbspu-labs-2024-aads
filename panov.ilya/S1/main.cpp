#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "list.hpp"

bool hasOverflow(unsigned long long num) {
  const unsigned long long overflowThreshold = std::numeric_limits<unsigned long long>::max() - 5;
  return (num >= overflowThreshold);
}

int main() {
  Panov::List<std::pair<std::string, std::vector<unsigned long long>>> sequences;

  std::string line;
  bool hasData = false;
  std::string temp;

  while (std::getline(std::cin, line) && !line.empty()) {
    std::istringstream iss(line);
    std::string word;
    iss >> word;
    temp = word;

    std::vector<unsigned long long> nums;
    unsigned long long num;
    bool hasOverflowFlag = false;
    while (iss >> num) {
      if (hasOverflow(num)) {
        hasOverflowFlag = true;
        break;
      }
      nums.push_back(num);
    }

    if (hasOverflowFlag) {
      std::cout << temp << std::endl;
      std::cerr << "Formed lists with exit code 1 and error message in standard error because of overflow in sequence" << std::endl;
      return 1;
    }

    sequences.push_back({ word, nums });

    if (!nums.empty())
      hasData = true;
  }

  if (sequences.empty()) {
    std::cout << 0 << '\n';
  }
  else {
    if (!hasData) {
      std::cout << temp << "\n" << 0 << "\n";
      return 0;
    }
    size_t max_length = 0;
    for (auto it = sequences.begin(); it != sequences.end(); ++it) {
      max_length = std::max(max_length, it->second.size());
    }

    for (auto it = sequences.begin(); it != sequences.end(); ++it) {
      std::cout << it->first;
      auto nextIt = it;
      ++nextIt;
      if (nextIt != sequences.end()) {
        std::cout << " ";
      }
    }
    std::cout << std::endl;

    size_t max_size = 0;
    for (const auto& pair : sequences) {
      const auto& sequence = pair.second;
      max_size = std::max(max_size, sequence.size());
    }

    for (size_t i = 0; i < max_size; ++i) {
      bool firstElement = true;
      for (const auto& pair : sequences) {
        const auto& sequence = pair.second;
        if (i < sequence.size()) {
          if (!firstElement) {
            std::cout << " ";
          }
          std::cout << sequence[i];
          firstElement = false;
        }
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
