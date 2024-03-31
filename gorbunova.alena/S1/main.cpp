#include "list.hpp"
#include <limits>

int main()
{
  gorbunova::List<std::pair<std::string, std::vector<unsigned long long>>> sequences;
  gorbunova::List<unsigned long long> sums;
  std::string input;
  std::string tempWord;
  bool isEmpty = true;
  bool flag = false;
  while (std::cin)
  {
    std::getline(std::cin, input);
    if (input.empty())
      break;
    isEmpty = false;
    std::string name;
    std::istringstream iss(input);
    iss >> name;
    tempWord = name;
    std::vector<unsigned long long> numbers;
    unsigned long long num;
    while (iss >> num)
    {
      numbers.push_back(num);
    }
    sequences.push_back(std::make_pair(name, numbers));
    if (numbers.empty())
    {
      flag = true;
    }
  }
  if (isEmpty)
  {
    std::cout << "0" << std::endl;
    return 0;
  }
  else
  {
    if (flag)
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
          std:cout << sequence[i];
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
            if (sum > std::numeric_limits<unsigned long long>::max() - (*it).second[i])
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
      std::cerr << e.what() << "\n";
      return 1;
    }
    for (auto it = sums.begin(); it != sums.end(); ++it)
    {
      std::cout << (*it);
      auto nextIt = it;
      ++nextIt;
      if (nextIt != sums.end())
      {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
  return 0;
}
