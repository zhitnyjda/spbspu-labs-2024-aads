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
  Panov::List<unsigned long long> sums;

  std::string input_line;
  bool data_available = false;
  std::string current_word;

  while (std::getline(std::cin, input_line) && !input_line.empty()) {
    std::istringstream iss(input_line);
    std::string word;
    iss >> word;
    current_word = word;

    std::vector<unsigned long long> numbers;
    unsigned long long num;
    while (iss >> num) {
      if (hasOverflow(num)) {
        std::cerr << "Overflow detected." << std::endl;
        return 1;
      }
      numbers.push_back(num);
    }

    sequences.push_back({ word, numbers });

    if (!numbers.empty())
      data_available = true;
  }

  if (sequences.empty()) {
    std::cout << 0 << '\n';
  }
  else {
    if (!data_available) {
      std::cout << current_word << "\n" << 0 << "\n";
      return 0;
    }
    size_t max_length = 0;
    for (auto it = sequences.begin(); it != sequences.end(); ++it) {
      max_length = std::max(max_length, it->second.size());
    }

    for (auto it = sequences.begin(); it != sequences.end(); ++it) {
      std::cout << it->first;
      auto next_it = it;
      ++next_it;
      if (next_it != sequences.end()) {
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
      bool first_element = true;
      for (const auto& pair : sequences) {
        const auto& sequence = pair.second;
        if (i < sequence.size()) {
          if (!first_element) {
            std::cout << " ";
          }
          std::cout << sequence[i];
          first_element = false;
        }
      }
      std::cout << std::endl;
    }

    for (size_t i = 0; i < max_length; ++i) {
      unsigned long long sum = 0;
      for (auto it = sequences.begin(); it != sequences.end(); ++it) {
        if (i < it->second.size()) {
          if (sum > std::numeric_limits<unsigned long long>::max() - it->second[i]) {
            std::cerr << "Overflow detected." << std::endl;
            return 1;
          }
          sum += it->second[i];
        }
      }
      sums.push_back(sum);
    }

    for (auto it = sums.begin(); it != sums.end(); ++it) {
      std::cout << (*it);
      auto next_it = it;
      ++next_it;
      if (next_it != sums.end()) {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }

  return 0;
}
