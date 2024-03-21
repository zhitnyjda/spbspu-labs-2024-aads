#include "doublelist.hpp"
#include "input_pairs.hpp"

using namespace kovshikov;
int main()
{
  DoubleList<std::pair<std::string, DoubleList<int>>> allPairs;
  inputPairs(allPairs);
  std::cout << allPairs.back().first << "\n";
  Iterator<int> backIterator = allPairs.back().second.begin();
  while(backIterator != nullptr)
  {
    std::cout << *backIterator << " ";
    backIterator++;
  }
  std::cout << allPairs.front().first << "\n";
  Iterator<int> frontIterator = allPairs.front().second.begin();
  while(frontIterator != nullptr)
  {
    std::cout << *frontIterator << " ";
    frontIterator++;
  }
 /* int i = 0;
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
  }*/
  return 0;
}

