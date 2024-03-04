#include <iostream>
#include <utility>
#include <cmath>
#include "list.hpp"
#include "divideFuncs.hpp"

int main()
{
  using namespace psarev;

  List< std::pair< std::string, List< int > > > lines;
  Iterator< std::pair< std::string, List< int > > > iterLine;
  std::string line = "";
  size_t maxDigits = 0;
  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string ord = psarev::getOrd(line);
      lines.pushBack({ ord, {} });
      iterLine = lines.begin();
      for (size_t i = 0; i < (lines.getSize() - 1); i++)
      {
        iterLine++;
      }
      size_t cntDigits = 0;
      while (line.size() != 0)
      {
        int digit = psarev::getDigit(line);
        (*iterLine).second.pushBack(digit);
        cntDigits++;
      }
      maxDigits = fmax(maxDigits, cntDigits);
    }
  }
  iterLine = lines.begin();
  for (size_t i = 0; i < lines.getSize(); i++)
  {
    std::cout << (*iterLine).first;
    if (i != lines.getSize())
    {
    std::cout << ' ';
    }
    iterLine++;
  }
  std::cout << '\n';
  Iterator< int > iterDig;
  List< int > sums;
  int curSum = 0;
  for (size_t i = 0; i < maxDigits; i++)
  {
    curSum = 0;
    iterLine = lines.begin();
    for (size_t j = 0; j < lines.getSize(); j++)
    {
      iterDig = (*iterLine).second.begin();
      if ((*iterLine).second.getSize() > i)
      {
        for (size_t k = 0; k < i; k++)
        {
          iterDig++;
        }
        if (curSum != 0)
        {
          std::cout << ' ' ;
        }
        std::cout << *iterDig;
        curSum += *iterDig;
      }
      iterLine++;
    }
    sums.pushBack(curSum);
    std::cout << '\n';
  }

  if (sums.getSize() == 0)
  {
    std::cout << 0;
  }
  else
  {
    Iterator< int > iterSums = sums.begin();
    for (size_t i = 0; i < sums.getSize(); i++)
    {
      std::cout << *iterSums;
      if (i != sums.getSize())
      {
        std::cout << ' ';
      }
      iterSums++;
    }
  }
  std::cout << '\n';

  return 0;
}
