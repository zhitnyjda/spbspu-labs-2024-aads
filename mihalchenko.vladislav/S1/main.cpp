#include <iostream>
#include <string>
#include "list.hpp"

using namespace mihalchenko;

int main()
{
  std::cout << "Hello World" << std::endl;

  // List<int> list;

  mihalchenko::List<std::pair<std::string, mihalchenko::List<int>>> mixedList;
  mihalchenko::List<int> integerList;
  std::string inputStr;
  std::string slovo;
  size_t lenMixList = 0;

  while (std::cin >> inputStr)
  {
    if (isdigit(inputStr[0]))
    {

      if (std::cin.peek() != '\n')
      {
        integerList.push_back(std::stoi(inputStr));
        std::cout << "cifra = " << inputStr << std::endl;
      }
      else
      {
        std::cout << "cifra = " << inputStr << std::endl;
        integerList.push_back(std::stoi(inputStr));
        mixedList.push_back(std::make_pair(slovo, integerList));
      }
    }
    else
    {
      slovo = inputStr;
      std::cout << "slovo = " << slovo << std::endl;
    }
    lenMixList++;
  }
  std::cout << "lenMixList = " << lenMixList << std::endl;

  return 0;
}
