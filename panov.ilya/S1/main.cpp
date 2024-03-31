#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "list.hpp"

bool hasOverflow(unsigned long long num) {
  const unsigned long long threshold = std::numeric_limits<unsigned long long>::max() - 5;
  return (num >= threshold);
}

int main() {
  Panov::List<std::pair<std::string, std::vector<unsigned long long>>> sequences;
  Panov::List<unsigned long long> sums;

  std::string line;
  bool has_data = false;
  std::string sequence_name;

  while (std::getline(std::cin, line) && !line.empty()) {
    std::istringstream iss(line);
    std::string word;
    iss >> word;
    sequence_name = word;

    std::vector<unsigned long long> numbers;
    unsigned long long num;
    bool overflow_flag = false;
    while (iss >> num) {
      if (hasOverflow(num)) {
        overflow_flag = true;
        break;
      }
      numbers.push_back(num);
    }

    if (overflow_flag) {
      std::cerr << "Formed lists with exit code 1 and error message in standard error because of overflow in sequence: " << sequence_name << std::endl;
      return 1;
    }

    sequences.push_back({ sequence_name, numbers });

    if (!numbers.empty())
      has_data = true;
  }

  if (sequences.empty()) {
    std::cout << 0 << '\n';
  }
  else {
    if (!has_data) {
      std::cout << sequence_name << "\n" << 0 << "\n";
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

    try {
      for (size_t i = 0; i < max_length; ++i) {
        unsigned long long total_sum = 0;
        for (auto it = sequences.begin(); it != sequences.end(); ++it) {
          if (i < it->second.size()) {
            if (total_sum > std::numeric_limits<unsigned long long>::max() - it->second[i]) {
              throw std::overflow_error("Overflow");
            }
            total_sum += it->second[i];
          }
        }
        sums.push_back(total_sum);
      }
    }
    catch (const std::overflow_error& e) {
      std::cerr << e.what() << '\n';
      return 1;
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
