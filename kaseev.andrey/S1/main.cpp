#include <iostream>
#include <cstring>
#include "MaineArray.hpp"

int main()
{
  kaseev::List<std::pair<char[100], kaseev::List<int>>> arr;
  char ListName[100];
  int List;
  while (true)
  {
    if (!(std::cin >> ListName))
    {
      break;
    }
    kaseev::List<int> numbers;
    while (std::cin.peek() != '\n' && std::cin >> List)
    {
      numbers.pushBack(List);
    }
    std::pair<char[100], kaseev::List<int>> list_pair;
    std::strcpy(list_pair.first, ListName);
    list_pair.second = numbers;
    arr.pushBack(list_pair);
    if (std::cin.eof())
    {
      break;
    }
  }
  for (size_t i = 0; i < arr.size(); ++i)
  {
    std::pair<char[100], kaseev::List<int>> list = arr[i];
    std::cout << list.first << " ";
  }
  std::cout << "\n";
  if (arr.empty())
  {
    std::cout << "0 \n";
    return 1;
  }
  bool finished = false;
  size_t index = 0;
  kaseev::List<int> sum;
  while (!finished)
  {
    finished = true;
    for (size_t i = 0; i < arr.size(); ++i)
    {
      std::pair<char[100], kaseev::List<int>> list = arr[i];
      if (index < list.second.size())
      {
        std::cout << list.second[index] << " ";
        sum[index] += list.second[index];
        finished = false;
      }
    }
    if (!finished)
    {
      std::cout << "\n";
    }
    index++;
  }
  for (size_t i = 0; i <= sum.size() - 2; i++)
  {
    std::cout << sum[i] << " ";
  }
  std::cout << "\n";
  return 0;
}


/*first 1 1 1
second 2 2 2 2
third
fourth 4 4
 */

