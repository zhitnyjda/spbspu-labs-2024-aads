#include <iostream>
#include <cstring>
#include <memory>
#include "list.hpp"

using namespace khoroshkin;

int main()
{
  size_t length = 10;
  std::unique_ptr<std::pair<std::string, List<int>>[]> allPairs(new std::pair<std::string, List<int>>[length]);
  std::string input;
  size_t count = -1;
  size_t maxLength = 0;
  bool seqWas = false;
  while (std::cin >> input)
  {
    if (isdigit(input[0]))
    {
      allPairs[count].second.push_back(std::stoi(input));
      seqWas = true;
    }
    else
    {
      if (count == length)
      {
        std::unique_ptr<std::pair<std::string, List<int>>[]> temp(new std::pair<std::string, List<int>>[length * 2]);
        std::copy(allPairs.get(), allPairs.get() + length, temp.get());
        allPairs = std::move(temp);
        length *= 2;
      }
      allPairs[++count] = std::pair< std::string, List< int > >(input, List< int >());
    }
    if (maxLength < allPairs[count].second.GetSize())
    {
      maxLength = allPairs[count].second.GetSize();
    }
  }
  if (!seqWas)
  {
    std::cout << 0;
  }
  for (size_t i = 0; i <= count; i++)
  {
    std::cout << allPairs[i].first;
    i == count ? std::cout << "\n" : std::cout << " ";
  }

  for (size_t i = 0; i < maxLength; i++)
  {
    for (size_t j = 0; j < length; j++)
    {
      if (allPairs[j].second.GetSize() > i)
      {
        std::cout << allPairs[j].second[i];
        j == length ? std::cout << "\n" : std::cout << " ";
      }
    }
    std::cout << "\n";
  }

  for (size_t i = 0; i < maxLength; i++)
  {
    int sum = 0;
    for (size_t j = 0; j < length; j++)
    {
      if (allPairs[j].second.GetSize() > i)
      {
        sum += allPairs[j].second[i];
      }
    }
    std::cout << sum;
    i + 1 == maxLength ? std::cout << "\n" : std::cout << " ";
  }
  for (size_t i = 0; i < length; i++)
  {
    allPairs[i].second.clear();
  }
  return 0;
}
