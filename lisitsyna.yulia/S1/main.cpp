#include <iostream>
#include <sstream>
#include <string>
#include "list.hpp"

int main()
{
  List<std::pair<std::string, List<int>>> sequences;
  std::string line;
  while (getline(std::cin, line))
  {
    std::istringstream iss(line);
    std::string name;
    iss >> name;
    List<int> nums;
    int num;
    while (iss >> num)
    {
      nums.push_back(num);
    }
    sequences.push_back(std::make_pair(name, nums));
  }
  for (size_t i = 0; i < sequences.GetSize(); ++i)
  {
    std::cout << sequences[i].first << " ";
  }
  std::cout << std::endl;
  size_t maxLen = 0;
  for (size_t i = 0; i < sequences.GetSize(); ++i)
  {
    if (sequences[i].second.GetSize() > maxLen)
    {
        maxLen = sequences[i].second.GetSize();
    }
  }
  for (size_t j = 0; j < maxLen; ++j)
  {
    for (size_t i = 0; i < sequences.GetSize(); ++i)
    {
      if (j < sequences[i].second.GetSize())
      {
            std::cout << sequences[i].second[j] << " ";
      }
    }
    std::cout << std::endl;
  }
  return 0;
}

