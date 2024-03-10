#include <iostream>
#include <string>
#include "list.hpp"
#include <utility>

using namespace mihalchenko;

int main()
{
  using mainList = mihalchenko::List<std::pair<std::string, mihalchenko::List<int>>>;
  mainList mixedList;
  using integerList = mihalchenko::List<int>;
  integerList intList1;

  std::string inputStr;
  std::string slovo;

  size_t maxLenOfSecondList = 0;
  size_t CountSecondList = 0;
  size_t CountmixedList = 0;

  integerList tempIntList;
  while (std::cin >> inputStr)
  {
    if (!isdigit(inputStr[0]))
    {
      slovo = inputStr;
      tempIntList.clear();
      CountSecondList = 0;

      mixedList.push_back(std::make_pair(slovo, tempIntList));
      CountmixedList++;

      if (std::cin.peek() == '\n')
      {
        // mixedList.push_back(std::make_pair(slovo, tempIntList));
        continue;
      }
    }
    else
    {
      mixedList[CountmixedList - 1].second.push_back(std::stoull(inputStr));
      CountSecondList++;
      if (std::cin.peek() == '\n')
      {
        if (maxLenOfSecondList < CountSecondList)
        {
          maxLenOfSecondList = CountSecondList;
        }
        continue;
      }
    }
  }

  // std::cout << "mixedList.size= " << mixedList.size_ << std::endl;
  // std::cout << "maxLenOfSecondList= " << maxLenOfSecondList << std::endl;
  // std::cout << "CountSecondList= " << CountSecondList << std::endl;

  for (size_t ind = 0; ind < mixedList.size_; ind++)
  {
    std::cout << mixedList[ind].first << " ";
  }
  std::cout << std::endl;

  size_t summa = 0;
  for (size_t numericView = 0; numericView < maxLenOfSecondList; numericView++)
  {
    summa = 0;
    for (size_t i = 0; i < mixedList.size_; i++)
    {
      if (mixedList[i].second.size_ > numericView)
      {
        std::cout << mixedList[i].second[numericView] << " ";
        summa = summa + mixedList[i].second[numericView];
      }
    }
    std::cout << std::endl;
    tempIntList.push_back(summa);
  }

  for (size_t i = 0; i < tempIntList.size_; i++)
  {
    std::cout << tempIntList[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
