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
        (*iter).second.push_back(num);
        firstLine = true;
        break;
      }
      (*iter).second.push_back(num);
    }
  }
  iter = seqsPair.begin();
  Iterator< std::pair< std::string, List< int > > > iterEnd = seqsPair.end();

  for (iter = seqsPair.begin(); iter != iterEnd; ++iter) {
    std::cout << iter->first << " ";
  }
  std::cout << "\n";

  iter = seqsPair.begin();
  Iterator< int > iterList = (*iter).second.begin();
  Iterator< int > iterListEnd = (*iter).second.end();
  size_t seqsPair_size = seqsPair.size();
  List< int > listSumm;
  int long long summ = 0;

  while (seqsPair_size > 0)
  {
    seqsPair_size = 0;
    summ = 0;
    for (iter = seqsPair.begin(); iter != iterEnd; ++iter)
    {
      iterList = (*iter).second.begin();
      if (iterList != nullptr)
      {
        std::cout << *iterList << " ";
        summ += *iterList;
        (*iter).second.pop_front();
        seqsPair_size += (*iter).second.size();
      }
    }
    listSumm.push_back(summ);
    std::cout << "\n";
  }

  Iterator< int > iterListSummEnd = listSumm.end();

  for (Iterator< int > iterListSumm = listSumm.begin(); iterListSumm != iterListSummEnd; ++iterListSumm) {
    std::cout << *iterListSumm << " ";
  }


  return 0;
}
