#include "funcDop.hpp"
#include <limits>

size_t mihalchenko::printName(mainList &mixedList, size_t mixedListSize, size_t maxLenOfSecondList)
{
  for (size_t i = 0; i < mixedListSize; i++)
  {
    std::cout << mixedList[i].first;
    if (i != mixedListSize - 1)
    {
      std::cout << " ";
    }
  }

  if (maxLenOfSecondList == 0)
  {
    std::cout << std::endl;
    std::cout << 0;
    return 0;
  }
  std::cout << std::endl;
  return 0;
}

size_t mihalchenko::printSumDigit(integerList &tempIntList, size_t tempIntListSize)
{
  for (size_t i = 0; i < tempIntListSize; i++)
  {
    std::cout << tempIntList[i];
    if (i != tempIntListSize - 1)
    {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
  return 0;
}

mihalchenko::t_ret mihalchenko::printMixedList(mainList &mixedList, size_t mixedListSize, size_t numericView, bool flgNewStr)
{
  size_t summa = 0;
  flgNewStr = true;
  summa = 0;
  size_t ullMax = std::numeric_limits<size_t>::max();
  for (size_t i = 0; i < mixedListSize; i++)
  {
    if (mixedList[i].second.getSize() > numericView)
    {
      if (flgNewStr)
      {
        std::cout << mixedList[i].second[numericView];
        flgNewStr = false;
      }
      else
      {
        std::cout << " " << mixedList[i].second[numericView];
      }
      if (ullMax - mixedList[i].second[numericView] >= summa)
      {
        summa = summa + mixedList[i].second[numericView];
      }
      else
      {
        std::cout << std::endl;
        std::cerr << "Input overflow!";
        t_ret t;
        t.summa = summa;
        t.flgNewStr = flgNewStr;
        t.resultFunc = false;
        return t;
      }
    }
  }
  std::cout << std::endl;
  t_ret t;
  t.summa = summa;
  t.flgNewStr = flgNewStr;
  t.resultFunc = true;
  return t;
}
