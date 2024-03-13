#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "list.hpp"
#include "node.hpp"

int main()
{
  hohlova::List<int> numbers;
  std::vector<std::string> words;
  std::string line;
  while (std::getline(std::cin, line) && !line.empty())
  {
    std::istringstream iss(line);
    std::string word;
    iss >> word;
    words.push_back(word);
    std::vector<int> nums;
    int num;
    while (iss >> num)
    {
      nums.push_back(num);
    }
    numbers.push_back(nums);
  }
  size_t max_length = 0;
  for (size_t i = 0; i < numbers.size(); ++i)
  {
    max_length = std::max(max_length, numbers[i].size());
  }
  for (const auto& word : words)
  {
    std::cout << word << " ";
  }
  std::cout << "\n";
  for (size_t i = 0; i < max_length; ++i)
  {
    for (size_t j = 0; j < numbers.size(); ++j)
    {
      if (i < numbers[j].size())
      {
        std::cout << numbers[j][i] << " ";
      }
    }
    std::cout << "\n";
  }
  for (size_t i = 0; i < max_length; ++i)
  {
    int sum = 0;
    for (size_t j = 0; j < numbers.size(); ++j)
    {
      if (i < numbers[j].size())
      {
        sum += numbers[j][i];
      }
    }
    std::cout << sum << " ";
  }
  std::cout << "\n";
  return 0;
}
