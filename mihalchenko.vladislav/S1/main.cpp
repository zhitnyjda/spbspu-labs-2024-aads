#include <iostream>
#include <string>
#include "list.hpp"
#include <utility>
#include <limits>

using namespace mihalchenko;

int main()
{
  using mainList = mihalchenko::List<std::pair<std::string, mihalchenko::List<size_t>>>;
  mainList mixedList;
  using integerList = mihalchenko::List<size_t>;
  integerList intList1;

  size_t ullMax = std::numeric_limits<size_t>::max();

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
      bool owerflow = false;
      std::string inputItog = "";

      std::string str = "";
      char counter = 0;
      if (inputStr.length() > 10)
      {
        owerflow = true;
      }
      else
      {
        while (str.length() <= 10)
        {
          str += inputStr[counter];
          if (str.length() == 10)
          {
            for (size_t i = 1000000000; i < ullMax; i++)
            {
              if (str == std::to_string(i))
              {
                inputItog = inputStr;
                break;
              }
            }
            if (inputItog == "")
            {
              owerflow = true;
            }
          }
          else
          {
            if (str == inputStr)
            {
              inputItog = inputStr;
              break;
            }
          }
        }
      }
      counter = 0;
      if (owerflow == true)
      {
        throw std::overflow_error("Input overflow!");
        return 1;
      }
      else
      {
        /*size_t wrem = 0;
          sscanf(inputStr.c_str(), "%zu", &wrem);
          mixedList[CountmixedList - 1].second.push_back(wrem);*/
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
