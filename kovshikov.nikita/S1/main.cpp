#include "doublelist.hpp"
#include "functions.hpp"

using namespace kovshikov;
int main()
{
  DoubleList<std::pair<std::string, DoubleList<int>>> allPairs;
  inputPairs(allPairs);
  outputListName(allPairs);
  outputResult(allPairs);
  return 0;
}

