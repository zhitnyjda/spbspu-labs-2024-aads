#include "doublelist.hpp"
#include "functions.hpp"

using namespace kovshikov;
int main()
{
  DoubleList<std::pair<std::string, DoubleList<int>>> allPairs;
  inputPairs(allPairs);
  outputListName(allPairs);

  DoubleList<DoubleList<int>> resultList;
  Iterator<std::pair<std::string, DoubleList<int>>> iteratorAllPairs = allPairs.begin();
  bool flag = true;
  while(flag == true)
  {
    DoubleList<int> list;
    while(iteratorAllPairs != allPairs.end())
    {
      if(!iteratorAllPairs->second.empty())
      {
        list.pushBack(iteratorAllPairs->second.front());
        iteratorAllPairs->second.popFront();
      }
      iteratorAllPairs++;
    }
    if(!list.empty())
    {
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
  return 0;
}

