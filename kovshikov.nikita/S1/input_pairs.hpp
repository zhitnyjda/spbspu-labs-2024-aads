#ifndef INPUT_HPP
#define INPUT_HPP
#include "doublelist.hpp"
#include <iostream>
#include <string>

namespace kovshikov
{
  void inputPairs(DoubleList<std::pair<std::string, DoubleList<int>>> &allPairs) //нужно ли принимать поток???
  {
    int i = 0;
    while(!std::cin.eof())
    {
      i++;
      std::cout << "pair number: " << i << "\n";
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
}

#endif
