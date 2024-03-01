#include <iostream>
#include <cstring>
#include <memory>
#include "list.hpp"

using namespace khoroshkin;

int main()
{
  List< std::pair< std::string, List< int > > > allPairs;
  std::string input;
  size_t count = -1;
  size_t maxLength = 0;
  while (std::cin >> input)
  {
    if (isdigit(input[0]))
    {
      allPairs[count].second.push_back(std::stoi(input));
    }
    else
    {
      allPairs.push_back({input,{}});
      count++;
    }
    if (maxLength < allPairs[count].second.getSize())
    {
      maxLength = allPairs[count].second.getSize();
    }
  }
  if (allPairs[0].second.isEmpty())
  {
    std::cout << 0;
    return 0;
  }


  /*for (size_t i = 0; i <= count; i++)
  {
    std::cout << allPairs[i].first;
    i == count ? std::cout << "\n" : std::cout << " ";
  }

  for (size_t i = 0; i < maxLength; i++)
  {
    for (size_t j = 0; j < length; j++)
    {
      if (allPairs[j].second.getSize() > i)
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
      if (allPairs[j].second.getSize() > i)
      {
        sum += allPairs[j].second[i];
      }
    }
    std::cout << sum;
    i + 1 == maxLength ? std::cout << "\n" : std::cout << " ";
  }*/
  return 0;
}
