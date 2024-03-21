#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "doublelist.hpp"
#include <iostream>
#include <string>

namespace kovshikov
{
  void inputPairs(DoubleList<std::pair<std::string, DoubleList<int>>> &allPairs)
  {
    int i = 0;
    while(!std::cin.eof())
    {
      i++;
      DoubleList<int> list;
      std::string listName;
      std::string integerString;
      std::cin >> listName;
      std::getline(std::cin, integerString);
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
        integer = std::stoi(tempString, nullptr, 10);
        list.pushBack(integer);
        allPairs.pushBack(std::pair<std::string, DoubleList<int>> {listName, list});
      }
    }
  }

  void outputListName(const DoubleList<std::pair<std::string, DoubleList<int>>> &allPairs)
  {
    Iterator<std::pair<std::string, DoubleList<int>>> iterator = allPairs.begin();
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
    }
  }
}

#endif
