#include "list.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
  std::string line;
  std::vector<std::pair<std::string, List<int>>> sequences;
  size_t maxLen = 0;
  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    std::string name;
    iss >> name;
    List<int> list;
    int num;
    size_t count = 0;
    while (iss >> num)
    {
      list.push_back(num);
      ++count;
    }
    maxLen = std::max(maxLen, count);
    sequences.emplace_back(name, std::move(list));
  }
  for (const auto& seq : sequences)
  {
    std::cout << seq.first << " ";
  }
  std::cout << "\n";
  std::vector<int> sums(maxLen, 0);
  for (const auto& seq : sequences)
  {
    std::cout << seq.first << " ";
  }
  std::cout << "\n";
  std::vector<int> sums(maxLen, 0);
}
