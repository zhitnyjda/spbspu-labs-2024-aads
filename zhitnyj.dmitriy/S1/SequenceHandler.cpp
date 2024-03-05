#include "SequenceHandler.h"
#include <iostream>
#include <vector>

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
  size_t maxLen = 0;
  for (const auto& seq : sequences)
  {
    maxLen = std::max(maxLen, seq.second.to_vector().size());
  }

  std::vector<unsigned long long> sums(maxLen, 0);
  for (size_t level = 0; level < maxLen; ++level)
  {
    for (const auto& seq : sequences)
    {
      auto elements = seq.second.to_vector();
      if (level < elements.size())
      {
        std::cout << elements[level] << " ";
        sums[level] += elements[level];
      }
    }
    std::cout << std::endl;
  }

  for (auto sum : sums)
  {
    std::cout << sum << " ";
  }

  if (sums.empty())
    std::cout << "0";

  std::cout << std::endl;
}
