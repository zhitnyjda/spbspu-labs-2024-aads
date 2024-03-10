#include <iostream>
#include <string>
#include <cstring>
#include "List.hpp"


int main()
{
  using namespace taskaev;
  List< std::pair< std::string, List < int > > > list;
  std::string name;
  List< int > nums;
  std::cin >> name;
  while(std::cin)
  {
    list.pushFront({name, nums});
    while (std::cin >> name && std::isdigit(name[0]))
    {
      list.front().second.pushFront(std::stoll(name));
    }
  }
  list.reverse();
  typename List<std::pair<std::string, List<int>>>::ListIterator< std::pair< std::string, List<int>>> i = list.begin();
  while(i != list.end())
  {
   std::cout << i->first << " ";
    ++i;
  }
  std::cout << "\n";
  return 0;
}
