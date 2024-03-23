#include "doublelist.hpp"
#include "functions.hpp"

using namespace kovshikov;
int main()
{
  DoubleList<std::pair<std::string, DoubleList<size_t>>> allPairs;
  bool isBigNumber = false;
  inputPairs(allPairs, isBigNumber);
  outputListName(allPairs);
  outputResult(allPairs, isBigNumber);
  return 0;
}

