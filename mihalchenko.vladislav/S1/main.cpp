#include <iostream>
#include <string>
#include "list.hpp"
#include <utility>

using namespace mihalchenko;

int main()
{
  std::cout << "Hello World" << std::endl;

  mihalchenko::List<std::pair<std::string, mihalchenko::List<int>>> mixedList;
  using integerList = mihalchenko::List<int>;
  integerList intList1;

  std::string inputStr;
  std::string slovo;

  bool flg = false;

  while (std::cin >> inputStr)
  {
    integerList tempIntList;

    if (!isdigit(inputStr[0]))
    {
      slovo = inputStr;
      // intList.clear();
      intList1 = tempIntList;
      // flg = true;
      // std::string ggg = "25";
      // intList.push_back(std::stoi(ggg));

      if (std::cin.peek() == '\n')
      {
        mixedList.push_back(std::make_pair(slovo, intList1));
        continue;
      }
    }
    else
    {
      tempIntList = intList1;
      // std::string ggg = "25";
      // integerList intList1;
      //  intList1.push_back(std::stoi(ggg));
      //  intList1.push_back(std::stoi(ggg));
      //  il2.push_back(std::stoi(inputStr));
      tempIntList.push_back(std::stoi(inputStr));

      if (std::cin.peek() == '\n')
      {
        /*for (size_t i = 0; i < intList.getSize(); i++)
        {
          std::cout << intList[i] << std::endl;
        }*/
        mixedList.push_back(std::make_pair(slovo, tempIntList));
        continue;
      }
    }
    // mixedList.push_back(std::make_pair(slovo, tempIntList));
  }

  for (size_t ind = 0; ind < mixedList.size_; ind++)
  {
    std::cout << mixedList[ind].first << std::endl;
    // std::cout << mixedList[ind].second << std::endl;
  }
  // return 0;
}
