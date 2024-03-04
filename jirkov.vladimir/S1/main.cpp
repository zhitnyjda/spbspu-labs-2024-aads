#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include "list.hpp"

int main() {
    jirkov::List<std::pair<std::string, std::vector<int>>> sequences;

  std::string name;
  while (std::cin >> name) {
    std::vector<int> sequence;
    int num;
    while (std::cin >> num) {
      sequence.push_back(num);
    }
    sequences.push_back({name, sequence});
  }
  for (const auto& pair : sequences) {
    std::cout << pair.first << " ";
  }
  std::cout << std::endl;
  std::vector<std::vector<int>> mergedSequences;
  int maxLength = 0;

  for (const auto& pair : sequences) {
    const auto& sequence = pair.second;
    maxLength = std::max(maxLength, static_cast<int>(sequence.size()));
  }

  for (int i = 0; i < maxLength; i++) {
    for (const auto& pair : sequences) {
      const auto& sequence = pair.second;
      if (i < sequence.size()) {
        mergedSequences[i].push_back(sequence[i]);
      }
    }
  }
  for (const auto& sequence : mergedSequences) {
    for (const auto& num : sequence) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
  std::vector<int> sums;

  for (const auto& sequence : mergedSequences) {
    int sum = 0;
    for (const auto& num : sequence) {
      sum += num;
    }
    sums.push_back(sum);
  }
  for (const auto& sum : sums) {
    std::cout << sum << " ";
  }
  std::cout << std::endl;
  return 0;
}
