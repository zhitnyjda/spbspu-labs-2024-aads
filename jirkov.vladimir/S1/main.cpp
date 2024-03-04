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
  std::cout << "Список названий списков:\n";
  for (const auto& pair : sequences) {
    std::cout << pair.first << " ";
  }
  std::cout << std::endl;
  std::vector<std::vector<int>> mergedSequences;
  size_t maxLength = 0;

  for (const auto& pair : sequences) {
    const auto& sequence = pair.second;
    maxLength = std::max(maxLength, sequence.size());
  }
  mergedSequences.resize(maxLength);

  for (size_t i = 0; i < maxLength; i++) {
    for (const auto& pair : sequences) {
      const auto& sequence = pair.second;
      if (i < sequence.size()) {
        mergedSequences[i].push_back(sequence[i]);
      }
    }
  }

  std::cout << "\nОбъединенные последовательности:\n";
  for (const auto& seq : mergedSequences) {
    for (const auto& num : seq) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

  int sum = 0;
  for (const auto& seq : mergedSequences) {
    for (const auto& num : seq) {
      sum += num;
    }
  }

  std::cout << "Сумма значений составленных списков:\n " << sum << std::endl;
  return 0;
}
