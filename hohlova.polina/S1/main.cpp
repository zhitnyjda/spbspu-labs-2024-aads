#include "list.hpp"

int main()
{
  hohlova::List<std::pair<std::string, std::vector<int>>> numbers;
  std::string line;

  while (std::getline(std::cin, line) && !line.empty())
  {
    std::istringstream iss(line);
    std::string word;
    iss >> word;

    std::vector<int> nums;
    int num;
    while (iss >> num)
    {
      nums.push_back(num);
    }
    numbers.push_back(std::make_pair(word, nums));
  }

  if (numbers.size() == 0)
  {
    std::cout << "0" << std::endl;
    return 0;
  }

  for (auto it = numbers.begin(); it != numbers.end(); ++it)
  {
    std::cout << (*it).first << " ";
  }
  std::cout << std::endl
    << numbers;

  size_t max_length = 0;
  for (auto it = numbers.begin(); it != numbers.end(); ++it)
  {
    max_length = std::max(max_length, (*it).second.size());
  }

  for (size_t i = 0; i < max_length; ++i)
  {
    int sum = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
      if (i < (*it).second.size())
        sum += (*it).second[i];
    }
    std::cout << sum << " ";
  }
  std::cout << std::endl;
  return 0;
}
