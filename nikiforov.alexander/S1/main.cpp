#include <iostream>
#include <string>
#include "list.hpp"

int main()
{
  using namespace nikiforov;

  std::string stroka;
  int num = 0;

  List< std::pair< std::string, List< int > > > seqs;
  Iterator< std::pair< std::string, List< int > > > iter = seqs.begin();
  bool firstLine = false;

  while (std::cin >> stroka)
  {
    if (!firstLine)
    {
      seqs.push_back({ stroka, {} });
      iter = seqs.begin();
    }
    else 
    {
      seqs.push_back({ stroka, {} });
      iter++;
    }
    
    while (std::cin >> num)
    {
      if (std::cin.peek() == '\n')
      {
        std::cout << num << "\n";
        (*iter).second.push_back(num);
        firstLine = true;
        break;
      }
      (*iter).second.push_back(num);
      std::cout << "num1" << "\n";
    }
    
  }
  
  return 0;
}
