#include <iostream>
#include <string>
#include "list.hpp"

int main()
{
  using namespace nikiforov;

  std::string stroka;
  int num = 0;

  List< std::pair< std::string, List< int > > > seqsPair;
  Iterator< std::pair< std::string, List< int > > > iter = seqsPair.begin();
  bool firstLine = false;

  while (std::cin >> stroka)
  {
    if (!firstLine)
    {
      seqsPair.push_back({ stroka, {} });
      iter = seqsPair.begin();
    }
    else
    {
      seqsPair.push_back({ stroka, {} });
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
  iter = seqsPair.begin();
  Iterator< std::pair< std::string, List< int > > > iterEnd = seqsPair.end();
  

  for (iter; iter != iterEnd; ++iter) {
    std::cout << iter->first << " ";
  }
  std::cout << "\n";


  iter = seqsPair.begin();
  Iterator< int > iterList = (*iter).second.begin();
  Iterator< int > iterListEnd = (*iter).second.end();
  size_t seqsPair_size = seqsPair.size();
  int long long summ = 0;

  while (seqsPair_size > 0)
  {
    seqsPair_size = 0;
    for (iter; iter != iterEnd; ++iter)
    {
      iterList = (*iter).second.begin();
      if (iterList != nullptr)
      {
        std::cout << *iterList << " ";
        (*iter).second.pop_front();
        seqsPair_size += (*iter).second.size();
      }
    }
    iter = seqsPair.begin();
    std::cout << "\n";
  }
  

  
  return 0;
}
