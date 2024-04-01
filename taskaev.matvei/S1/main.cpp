#include <iostream>
#include <limits>
#include <utility>
#include <string>
#include "List.hpp"


int main()
{
  using namespace taskaev;
  List< std::pair< std::string, List < size_t > > > list;
  std::string name = "";
  std::cin >> name;
  while(std::cin)
  {
    list.pushFront({ name, List<size_t>()});
    while(std::cin >> name && !std::isalpha(name[0]))
    {
      list.front().second.pushBack(std::stoull(name));
    }
  }
  if(list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  list.reverse();
  List<std::pair<std::string, List<size_t>>>::Iterator iterator = list.begin();
  while(iterator != list.end())
  {
    std::cout << iterator->first;
    if(++iterator != list.end())
    {
      std::cout << " ";
    }
  }
  List<size_t> sums;
  size_t maxNum = 1;
  iterator = list.begin();
  while (iterator != list.end())
  {
    size_t j = 0;
    auto it = iterator->second.begin();
    while (it != iterator->second.end())
    {
      j++;
      maxNum = (maxNum > j) ? maxNum : j;
      it++;
    }
    iterator++;
  }
  if (maxNum != 1)
  {
    std::cout << "\n";
  }
  bool bools = false;
  size_t sum;
  size_t j = 0;
  const size_t maxLimit = std::numeric_limits< size_t >::max();
  while (j < maxNum)
  {
    j++;
    sum = 0;
    iterator = list.begin();
    while (iterator != list.end())
    {
      List<size_t>& twoList =  const_cast<List<size_t>&>(iterator->second);
      if (!twoList.empty())
      {
        if (sum > 0 || bools)
        {
          std::cout << " ";
        }
        if (maxLimit - sum >= twoList.front())
        {
          sum += twoList.front();
        }
        else
        {
          bools = true;
        }
        std::cout << twoList.front();
        twoList.popFront();
      }
      iterator++;
    }
    std::cout << "\n";
    sums.pushFront(sum);
    if (bools)
    {
      std::cerr << " Stack Overflow error!\n";
      return 1;
    }
  }
  sums.reverse();
  List<size_t>::Iterator iteratorSums = sums.begin();
  if(!sums.empty())
  {
    while(iteratorSums != sums.end())
    {
      std::cout << *iteratorSums;
      if(++iteratorSums != sums.end())
      {
        std::cout << " ";
      }
    }
  }
  else
  {
    std::cout << "0\n";
  }
  std::cout << "\n";
  return 0;
}
