#include <iostream>
#include <limits>
#include <utility>
#include <string>
#include "List.hpp"


int main()
{
  using namespace taskaev;
  List< int > sums;
  List< std::pair< std::string, List < int > > > list;
  std::string name;
  std::cin >> name;
  while(std::cin)
  {
    list.pushFront({name, List<int>()});
    while (std::cin >> name && std::isalpha(name[0]))
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
  typename List<std::pair<std::string, List<int>>>::ListIterator< std::pair< std::string, List<int>>> i = list.begin();
  while(i != list.end())
  {
    std::cout << i->first;
    if(i++ != list.end())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  int maxNum = 1;
  i = list.begin();
  while (i != list.end())
  {
    int j = 0;
    auto it = i->second.begin();
    while (it != i->second.end())
    {
      j++;
      maxNum = (maxNum > j) ? maxNum : j;
      it++;
    }
    i++;
  }
  bool bools = false;
  int j = 0;
  int sum;
  const int maxLimit = std::numeric_limits< int >::max();
  while (j < maxNum)
  {
    j++;
    sum = 0;
    i = list.begin();
    while (i != list.end())
    {
      if (!i->second.empty())
      {
        if (sum > 0 || bools)
        {
          std::cout << " ";
        }
        std::cout << i->second.front();
        if (maxLimit - sum <= i->second.front())
        {
          sum += i->second.front();
        }
        else
        {
          bools = true;
        }
        i->second.popFront();
      }
      i++;
    }
    std::cout << "\n";

    if (bools)
    {
      std::cerr << " Stack Overflow error!\n";
      return 1;
    }
    sums.pushFront(sum);
  }
  sums.reverse();
  typename List<int>::ListIterator<int> is = sums.begin();
  while(is != sums.end())
  {
    std::cout << *is;
    if(is++ != sums.end())
    {
      std::cout << " ";
    }
  }
  return 0;
}
