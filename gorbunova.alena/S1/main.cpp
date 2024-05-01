#include <limits>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "list.hpp"

void printSums(gorbunova::List< unsigned long long > sums)
{
  for (auto it = sums.begin(); it != sums.end(); ++it)
  {
    std::cout << (*it);
    auto nextIt = it;
    ++nextIt;
    if (nextIt != sums.end())
    {
      std::cout << " ";
    }
    std::cout << std::endl;
}

void printSequences(gorbunova::List<std::pair<std::string, std::vector< unsigned long long >>> sequences)
{
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    std::cout << (*it).first;
    auto nextIt = it;
    ++nextIt;
    if (nextIt != sequences.end())
    {
      std::cout << " ";
    }
  }
    std::cout << std::endl;
}

std::vector<std::string> splitString(const std::string &input)
{
  std::vector<std::string> result;
  std::string word;
  for (char c : input)
  {
    if (c == ' ')
    {
      if (!word.empty())
      {
        result.push_back(word);
        word.clear();
      }
    }
    else
    {
      word += c;
    }
  }
  if (!word.empty())
  {
    result.push_back(word);
  }
  return result;
}

int main()
{
  gorbunova::List<std::pair<std::string, std::vector< unsigned long long >>> sequences;
  gorbunova::List< unsigned long long > sums;
  std::string input;
  std::string tempWord;
  bool isEmpty = true;
  bool containsEmptySequence = false;
  while (std::getline(std::cin, input));
  {
    if (input.empty())
      break;
    isEmpty = false;
    auto words = splitString(input);
    tempWord = words[0];
    std::vector< unsigned long long > numbers;
    for (size_t i = 1; i < words.size(); ++i)
    {
      numbers.push_back(std::stoull(words[i]));
    }
    sequences.push_back(std::make_pair(tempWord, numbers));
    if (numbers.empty())
    {
      containsEmptySequence = true;
    }
  }
  if (isEmpty)
  {
    std::cout << 0 << std::endl;
    return 0;
  }
  else
  {
    if (containsEmptySequence && sequences.getSize() == 1)
    {
      std::cout << tempWord << "\n"
                << 0 << "\n";
      return 0;
    }
    size_t max_size = 0;
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      max_size = std::max(max_size, (*it).second.size());
    }
    printSequences(sequences);
    for (size_t i = 0; i < max_size; ++i)
    {
      bool firstElement = true;
      for (const auto &pair : sequences)
      {
        const auto &sequence = pair.second;
        if (i < sequence.size())
        {
          if (!firstElement)
          {
            std::cout << " ";
          }
          std::cout << sequence[i];
          firstElement = false;
        }
      }
      std::cout << std::endl;
    }
    try
    {
      for (size_t i = 0; i < max_size; ++i)
      {
        unsigned long long sum = 0;
        for (auto it = sequences.begin(); it != sequences.end(); ++it)
        {
          if (i < (*it).second.size())
          {
            if (sum > std::numeric_limits< unsigned long long >::max() - (*it).second[i])
            {
              throw std::overflow_error("Overflow");
            }
            sum += (*it).second[i];
          }
        }
        sums.push_back(sum);
      }
    }
    catch (const std::overflow_error &e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
    printSums(sums);
  }
  return 0;
}
