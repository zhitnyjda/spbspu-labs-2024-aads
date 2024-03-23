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

  void outputResult(const DoubleList<std::pair<std::string, DoubleList<int>>> &allPairs)
  {
    DoubleList<int> summaList;
    DoubleList<DoubleList<int>> resultList;
    Iterator<std::pair<std::string, DoubleList<int>>> iteratorAllPairs = allPairs.begin();
    bool flag = true;
    while(flag == true)
    {
      int summa = 0;
      DoubleList<int> list;
      while(iteratorAllPairs != allPairs.end())
      {
        if(!iteratorAllPairs->second.empty())
        {
          summa += iteratorAllPairs->second.front();
          list.pushBack(iteratorAllPairs->second.front());
          iteratorAllPairs->second.popFront();
        }
        iteratorAllPairs++;
      }
      if(!list.empty())
      {
        summaList.pushBack(summa);
        resultList.pushBack(list);
        iteratorAllPairs = allPairs.begin();
      }
      else
      {
        flag = false;
      }
    }
    while(!resultList.empty())
    {
      DoubleList<int> list = resultList.front();
      while(!list.empty())
      {
        std::cout << list.front();
        list.popFront();
        if(!list.empty())
        {
          std::cout << " ";
        }
      }
      resultList.popFront();
      std::cout << "\n";
    }
    while(!summaList.empty())
    {
      std::cout << summaList.front();
      summaList.popFront();
      if(!summaList.empty())
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
