#include <iostream>
#include "doublelist.hpp"
#include <utility>
#include <string>

using namespace kovshikov;
int main()
{
 /* std::string string = " 2 52 2 2 32";
  std::cout << string[0] << "\n";
  std::cout << string.length() << "\n";
  std::string tempString = "";
  for(size_t i = 0; i < string.length(); i++)
  {
    if(string[i] != ' ')
    {
      tempString.append(1, string[i]);
    }
    else
    {
      if(!tempString.empty())
      {
        int integer = std::stoi(tempString, nullptr, 10);
        std::cout << integer << "\n";
        tempString.clear();
      }
    }
  }
  int integer = std::stoi(tempString, nullptr, 10);
  std::cout << integer << "\n";*/

  DoubleList<std::pair<std::string, DoubleList<int>>> allPairs; //список всех пар
  int i = 0;
  while(!std::cin.eof()) // производится ввод, до момента ctrl + D
  {
    i++;
    std::cout << "pair number: " << i << "\n";
    DoubleList<int> list;
    std::string listName;
    std::string integerString;
    std::cin >> listName; //запишется наименование последовательности
    std::getline(std::cin, integerString); //вводятся числа в качестве строки
    if(!listName.empty())
    {
      std::string tempString;
      int integer;
      for(size_t i = 0; i < integerString.length(); i++)
      {
        if(integerString[i] != ' ')
        {
          tempString.append(1, integerString[i]);
        }
        else
        {
          if(!tempString.empty())
          {
            integer = std::stoi(tempString, nullptr, 10);
            list.pushBack(integer);
            tempString.clear();
          }
        }
      }
      integer = std::stoi(tempString, nullptr, 10); //проверка на пустоту строки
      list.pushBack(integer);
      std::pair<std::string, DoubleList<int>> element = {listName, list};
      allPairs.pushBack(element);
    }
  }
  return 0;
}
