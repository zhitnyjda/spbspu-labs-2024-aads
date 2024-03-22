#include "list.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

int main()
{
  std::string line;
  std::vector<std::pair<std::string, List<long long>>> sequences;
  size_t maxLen = 0;
  while (std::getline(std::cin, line) && !line.empty())
  {
    std::istringstream iss(line);
    std::string name;
    iss >> name;
    List<long long> list;
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
  if (!sequences.empty())
  {
    std::cout << 0 << "\n";
  }
  for (size_t i = 0; i < maxLen; ++i)
  {
    for (const auto& seq : sequences)
    {
      const auto& list = seq.second;
      auto it = list.begin();
      std::advance(it, i);
      if (it != list.end())
      {
        std::cout << *it << " ";
      }
      else
      {
        std::cout << "0 ";
      }
    }
    if (!sequences.empty())
    {
      std::cout << 0 << "\n";
    }
  }
  std::vector<long long> sums(maxLen, 0);
  for (size_t i = 0; i < maxLen; ++i)
  {
    for (const auto& seq : sequences)
    {
      const auto& list = seq.second;
      auto it = list.begin();
      std::advance(it, i);
      if (it != list.end())
      {
        sums[i] += *it;
      }
    }
  }
  bool foundNonZero = false;
  for (auto sum : sums)
  {
    if (sum != 0)
    {
      foundNonZero = true;
    }
    if (foundNonZero)
    {
      std::cout << sum << " ";
    }
  }
  if (!sequences.empty())
  {
    std::cout << 0 << "\n";
  }
  return 0;
}
