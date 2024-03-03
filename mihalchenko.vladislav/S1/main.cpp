#include <iostream>
#include <string>
#include "list.hpp"

using namespace mihalchenko;

int main()
{
  std::cout << "Hello World" << std::endl;

  List<int> list;

  mihalchenko::List<std::pair<std::string, mihalchenko::List<int>>> mixedList;
  mihalchenko::List<int> integerList;
  std::string inputStr;
  std::string slovo;
  size_t lenMixList = 0;

  while ((std::cin >> inputStr) && (!std::cin.eof()) && (!std::cin.fail()))
  {
    if (std::cin.peek() == '\n')
    {
      continue;
    }
    if (!isdigit(inputStr[0]))
    {
      slovo = inputStr;
      // std::cout << "slovo = " << slovo << std::endl;
    }
    else
    {
      if (std::cin.peek() != '\n')
      {
        integerList.push_back(std::stoi(inputStr));
        // std::cout << "cifra = " << inputStr << std::endl;
      }
      else
      {
        std::cout << "cifra 2 = " << inputStr << std::endl;
        integerList.push_back(std::stoi(inputStr));
        mixedList.push_back(std::make_pair(slovo, integerList));
        std::cout << "cifra 3 = " << inputStr << std::endl;
      }
    }
    lenMixList++;
  }
  std::cout << "lenMixList = " << lenMixList << std::endl;

  /*for (auto it = mixedList.begin(); it != mixedList.end(); ++it)
  {
    std::cout << it->first;
  }*/

  for (size_t ind = 0; ind < list.size_; ind++)
  {
    // std::cout << mixedList[ind].first;
  }

  return 0;
}
