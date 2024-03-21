#include "doublelist.hpp"
#include "functions.hpp"

using namespace kovshikov;
int main()
{
  DoubleList<std::pair<std::string, DoubleList<int>>> allPairs;
  inputPairs(allPairs);
  outputListName(allPairs);
 /* Iterator<std::pair<std::string, DoubleList<int>>> iterator = allPairs.begin();
  while(iterator != nullptr)
  {
    std::cout << iterator->first;
    iterator++;
    if(iterator != nullptr)
    {
      std::cout << " ";
    }
    else
    {
      std::cout << "\n";
    }
  }*/
  return 0;
}

