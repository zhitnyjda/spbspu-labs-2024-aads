lisitsyna::#include "list.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <stdexcept>

namespace
{
  unsigned long long sum(unsigned long long a, unsigned long long b)
  {
    if (a > std::numeric_limits< unsigned long long >::max() - b)
    {
      throw std::overflow_error("Overflow!");
    }
    return a + b;
  }
}
int main()
{
  lisitsyna::List< std::pair< std::string, List< unsigned long long > > > sequences;
  size_t maxLen = 0;
  while (!std::cin.eof() && !std::cin.fail())
  {
    std::string name, numbers;
    std::cin >> name;
    if (name.empty())
    {
      continue;
    }
    std::getline(std::cin, numbers);
    lisitsyna::List< unsigned long long > list;
    if (numbers.empty())
    {
      sequences.push_back({ name, std::move(list) });
      continue;
    }
    size_t count = 0;
    std::string number;
    for (size_t i = 0; i < numbers.length(); ++i)
    {
      if (std::isdigit(numbers[i]))
      {
        number += numbers[i];
      }
      else if (!number.empty())
      {
        unsigned long long num = std::stoull(number);
        list.push_back(num);
        number.clear();
        ++count;
      }
    }
    if (!number.empty())
    {
      unsigned long long num = std::stoull(number);
      list.push_back(num);
      ++count;
    }
    maxLen = std::max(maxLen, count);
    sequences.push_back({ name, std::move(list) });
  }
  bool first = true;
  for (const auto & seq: sequences)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      std::cout << ' ';
    }
    std::cout << seq.first;
  }
  if (sequences.empty())
  {
    std::cout << 0 << '\n';
    return 0;
  }
  std::cout << '\n';
  for (size_t i = 0; i < maxLen; ++i)
  {
    first = true;
    for (const auto & seq: sequences)
    {
      const auto & list = seq.second;
      auto it = list.begin();
      for (size_t j = 0; j < i && it != list.end(); ++j)
      {
        ++it;
      }
      if (it != list.end())
      {
        if (first)
        {
          first = false;
        }
        else
        {
          std::cout << ' ';
        }
        std::cout << *it;
      }
    }
    std::cout << '\n';
    if (sequences.empty())
    {
      std::cout << 0;
    }
  }
  lisitsyna::List < unsigned long long > sums;
  try
  {
    for (size_t i = 0; i < maxLen; ++i)
    {
      sums.push_back(0);
      for (const auto & seq: sequences)
      {
        const auto & list = seq.second;
        auto it = list.begin();
        for (size_t j = 0; j < i && it != list.end(); ++j)
        {
          ++it;
        }
        if (it != list.end())
        {
          sums.back() = sum(sums.back(), *it);
        }
      }
    }
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  first = true;
  bool foundNonZero = false;
  for (auto sum: sums)
  {
    if (sum != 0)
    {
      foundNonZero = true;
    }
    if (foundNonZero)
    {
      if (first)
      {
        first = false;
      }
      else
      {
        std::cout << ' ';
      }
      std::cout << sum;
    }
  }
  if (sums.empty())
  {
    std::cout << '0';
  }
  std::cout << '\n';
  return 0;
}
