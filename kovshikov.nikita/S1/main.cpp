#include <iostream>
#include "doublelist.hpp"
#include <string>

using namespace kovshikov;
int main()
{
  DoubleList<std::pair<std::string, int>> allPairs;
  std::string str = "nikita";
  int num = 9;
  allPairs.pushBack({str, num});
 // std::cout << allPairs.front().second << "\n";





  //сохранить все последовательности в allPairs;


 return 0;
}
