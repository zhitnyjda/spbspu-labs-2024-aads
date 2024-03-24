#include "list.hpp"

int main()
{
  hohlova::List<std::pair<std::string, std::vector<int>>> numbers;
  std::string line;
  bool hasData = false;
  std::string temp;

  while (std::getline(std::cin, line) && !line.empty())
  {
    std::istringstream iss(line);
    std::string word;
    iss >> word;
    temp = word;

    std::vector<int> nums;
    std::string numStr;
    while (iss >> numStr)
    {
      try
      {
        int num = std::stoi(numStr);
        nums.push_back(num);
      }
      catch (const std::invalid_argument& ia)
      {
        std::cerr << ia.what() << "\n";
        return 1;
      }
      catch (const std::out_of_range& oor)
      {
        std::cerr << oor.what() << "\n";
        return 1;
      }
    }

  numbers.push_back(std::make_pair(word, nums));
  if (!nums.empty())
    hasData = true;
  }
  if (!hasData)
  {
    std::cout << temp << std::endl
      << "0";
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

  return 0;
}

