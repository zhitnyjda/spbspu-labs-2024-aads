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

  List< std::pair< std::string, int> > seqs;
  seqs.push_back(std::pair< std::string, int>("lol", 2));
  Iterator< std::pair< std::string, int> > iter = seqs.begin();

  std::cout << iter->first << '\n';


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
