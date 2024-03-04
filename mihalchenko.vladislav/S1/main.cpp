#include <iostream>
#include <string>
#include "list.hpp"
#include <utility>

using namespace mihalchenko;

int main()
{
  mihalchenko::List<std::pair<std::string, mihalchenko::List<int>>> mixedList;
  using integerList = mihalchenko::List<int>;
  integerList intList1;

  std::string inputStr;
  std::string slovo;

  using iter = mihalchenko::List<int>::Iterator<int>;

  // bool flg = false;

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
      tempIntList.push_back(std::stoi(inputStr));
      // std::cout << std::stoi(inputStr) << " ";

      if (std::cin.peek() == '\n')
      {
        /*for (size_t i = 0; i < intList.getSize(); i++)
        {
          std::cout << intList[i] << std::endl;
        }*/
        mixedList.push_back(std::make_pair(slovo, tempIntList));
        // mixedList.push_back(std::pair(slovo, tempIntList));
        continue;
      }
    }
    // mixedList.push_back(std::make_pair(slovo, tempIntList));
  }

  for (size_t ind = 0; ind < mixedList.size_; ind++)
  {
    std::cout << mixedList[ind].first << " ";
  }
  std::cout << std::endl;

  for (size_t ind = 0; ind < mixedList.size_; ind++)
  {
    iter it = mixedList[ind].second[0];
    it = mixedList[ind].second[0];
    std::cout << it.data_;
  }

  /*for (size_t ind = 0; ind < mixedList.getSize(); ind++)
  {
    // std::cout << mixedList[ind].second << std::endl;
    // integerList intList2;
    std::cout << mixedList.begin().data_.second;
    /* for (size_t i = 0; i < mixedList[ind].second.getSize() - 1; i++)
    {
      intList2[i] = mixedList[ind].second[i];
      std::cout << intList2[i] << " ";
    }*/
  // std::cout << mixedList[ind].second[1] << std::endl;}*/

  return 0;
}
