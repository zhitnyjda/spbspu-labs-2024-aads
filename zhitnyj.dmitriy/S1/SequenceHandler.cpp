#include <iostream>
#include <limits>
#include "SequenceHandler.h"

void SequenceHandler::addSequence(const std::string& name, const List<unsigned long long>& sequence)
{
  names.push_back(name);
  sequences.push_back(sequence);
}

void SequenceHandler::printSequences()
{
  for (auto it = names.begin(); it != names.end(); ++it)
  {
    std::cout << *it << (it + 1 == names.end() ? "" : " ");
  }
  if (*names.begin() != "")
  {
    std::cout << "\n";
  }
}

void SequenceHandler::rearrangeAndPrint()
{
  size_t maxLen = 0;
  for (auto& seq : sequences)
  {
    maxLen = std::max(maxLen, seq.size());
  }

  unsigned long long* sums = new unsigned long long[maxLen]{};

  int s = 0;
  for (size_t i = 0; i < maxLen; ++i)
  {
    for (const auto& seq : sequences)
    {
      auto it = seq.begin();

      for (size_t j = 0; j < i && it != seq.end(); ++j) {
        ++it;
      }
      if (it != seq.end())
      {
        std::cout << (s ? " " : "");
        s = 1;
        std::cout << *it;
        if (sums[i] > std::numeric_limits<unsigned long long>::max() - *it)
        {
          std::cout << "\n";
          delete[] sums;
          throw std::overflow_error("Sum of numbers is too big.");
        }
        sums[i] += *it;
      }
    }
    std::cout << "\n";
    s = 0;
  }

  if (!maxLen)
  {
    std::cout << "0\n";
  }

  for (size_t i = 0; i < maxLen; ++i)
  {
    std::cout << sums[i] << (i == (maxLen - 1) ? "\n" : " ");
  }

  delete[] sums;
}
