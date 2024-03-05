#include <iostream>
#include <string>
#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  List< std::pair< std::string, List< int > > > seqsPair;
  Funcs< int > func;

  func.input_(std::cin, seqsPair);
  func.outputName_(seqsPair);

  List< int > listSumm;
  Iterator< std::pair< std::string, List< int > > > iter = seqsPair.begin();
  Iterator< std::pair< std::string, List< int > > > iterEnd = seqsPair.end();
  Iterator< int > iterList = (*iter).second.begin();
  Iterator< int > iterListEnd = (*iter).second.end();

  size_t seqsPair_size = seqsPair.size();

  int long long summ = 0;

  bool flag = false;

  while (seqsPair_size > 0)
  {
    seqsPair_size = 0;
    summ = 0;
    for (iter = seqsPair.begin(); iter != iterEnd; ++iter)
    {
      iterList = (*iter).second.begin();
      if (iterList != nullptr)
      {
        if (flag == true)
        {
          std::cout << " ";
        }
        std::cout << *iterList;
        summ += *iterList;
        (*iter).second.pop_front();
        seqsPair_size += (*iter).second.size();
        flag = true;
      }
    }
    flag = false;
    listSumm.push_back(summ);
    std::cout << "\n";
  }

  Iterator< int > iterListSummEnd = listSumm.end();
  flag = false;

  for (Iterator< int > iterListSumm = listSumm.begin(); iterListSumm != iterListSummEnd; ++iterListSumm)
  {
    if (flag == true)
    {
      std::cout << " ";
    }
    std::cout << *iterListSumm;
    flag = true;
  }
  std::cout << "\n";

  return 0;
}
