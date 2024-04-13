#include <iostream>
#include "doublelist.hpp"
#include "functions.hpp"

int main()
{
  kovshikov::listPair allPairs;
  bool isBigNumber = false;
  kovshikov::inputPairs(allPairs, isBigNumber);
  kovshikov::outputListName(allPairs);
  kovshikov::DoubleList< size_t > summaList;
  kovshikov::listOfList resultList;
  kovshikov::processInput(summaList, resultList, allPairs);
  kovshikov::outputResult(isBigNumber, summaList, resultList);
  if(isBigNumber == true)
  {
    std::cerr << "too many numbers were entered\n";
    return 1;
  }
  return 0;
}
