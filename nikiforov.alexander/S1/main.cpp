#include <iostream>
#include <string>
#include "list.hpp"

int main()
{
  using namespace nikiforov;

  std::string input;
  std::string stroka;
  input = "lol";
  int num = 0;
  /*std::pair<std::string, List< int >> listPair;
  List < std::pair< std::string, List< int >> > allListsPairs;
  Iterator< List< int > > iter = allListsPairs.begin();
  List<int> lst;
  lst.push_back(12);
  lst.push_back(10);
  std::cout << iter->first << '\n';*/
  List< int > list;  
  List< std::pair< std::string, List< int > > > seqs;
  seqs.push_back({ input, {} });
  Iterator< std::pair< std::string, List< int > > > iter = seqs.begin();
  (*iter).second.push_back(14);
  (*iter).second.push_back(12);
  (*iter).second.push_back(18);
  Iterator< int > iterList = (*iter).second.begin();
  Iterator< int > iterListEnd = (*iter).second.end();
  
  std::cout << iter->first << '\n';
  for (iterList; iterList != iterListEnd; ++iterList) {
    std::cout << *iterList << " ";
  }

  std::cout << '\n';
  while (std::cin >> stroka)
  {
    if (std::cin.peek() == '\n')
    {
      continue;
    }

    while (std::cin >> num)
    {
      if (std::cin.peek() == '\n')
      {
        std::cout << num << "\n";
        break;
      }
      std::cout << num << "\n";
    }

  }
  return 0;
}
