#include "SequenceHandler.h"
#include <iostream>
#include <vector>
#include <algorithm>

void SequenceHandler::addSequence(const std::string& name, const List<unsigned long long>& sequence)
{
  sequences.push_back({ name, sequence });
}

void SequenceHandler::printSequences()
{
  for (const auto& pair : sequences)
  {
    std::cout << pair.first << " ";
  }
  std::cout << std::endl;
}

void SequenceHandler::rearrangeAndPrint()
{
  std::vector<std::vector<int>> numbers;
  int maxLen = 0;

  for (const auto& seq : sequences)
  {
    int len = 0;
    for (auto it = seq.second.begin(); it != seq.second.end(); ++it)
    {
      len++;
    }
    maxLen = std::max(maxLen, len);
  }

  for (int i = 0; i < maxLen; ++i)
  {
    std::vector<int> row;
    for (const auto& seq : sequences)
    {
      auto it = seq.second.begin();
      for (int j = 0; j < i; ++j)
      {
        if (it != seq.second.end()) ++it;
      }
      if (it != seq.second.end()) row.push_back(*it);
    }
    if (!row.empty()) numbers.push_back(row);
  }

  std::vector<int> sums;
  for (const auto& row : numbers)
  {
    int sum = 0;
    for (int num : row)
    {
      std::cout << num << " ";
      sum += num;
    }
    std::cout << std::endl;
    sums.push_back(sum);
  }

  for (int sum : sums)
  {
    std::cout << sum << " ";
  }
  if (!sums.empty()) std::cout << std::endl;
}
