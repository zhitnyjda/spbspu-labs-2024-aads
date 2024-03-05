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

  integerList tempIntList;
  while (std::cin >> inputStr)
  {
    integerList tempIntList;

    if (!isdigit(inputStr[0]))
    {
      slovo = inputStr;
      tempIntList.clear();
      // integerList tempIntList;

      if (std::cin.peek() == '\n')
      {
        mixedList.push_back(std::make_pair(slovo, tempIntList));
        continue;
      }
    }
    else
    {
      tempIntList.push_back(std::stoi(inputStr));
      // std::cout << "tempIntList.Size = " << tempIntList.size_ << " tempIntList[0] = " << tempIntList[0] << std::endl;
      if (std::cin.peek() == '\n')
      {
        // int tempIntList[5] = {1, 2, 3, 4, 5};
        // auto p2 = std::make_pair(slovo, tempIntList);
        mixedList.push_back(std::make_pair(slovo, tempIntList));
        if (maxLenOfSecondList < tempIntList.size_)
        {
          maxLenOfSecondList = tempIntList.size_;
        }
        continue;
      }
    }
  }

  std::cout << "mixedList.size= " << mixedList.size_ << std::endl;
  std::cout << "maxLenOfSecondList= " << maxLenOfSecondList << std::endl;

  for (size_t ind = 0; ind < mixedList.size_; ind++)
  {
    std::cout << mixedList[ind].first << " ";
  }
  std::cout << std::endl;

  integerList summaEveryString;
  size_t summa = 0;
  // maxLenOfSecondList = 4;
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
    summaEveryString.push_back(summa);
  }

  for (size_t ind = 0; ind < maxLenOfSecondList; ind++)
  {
    std::cout << summaEveryString[ind] << " ";
  }
  std::cout << std::endl;

  return 0;
}
