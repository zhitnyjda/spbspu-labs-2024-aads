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

    if (std::cin.peek() == '\n')
    {
      continue;
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

  bool flag = false;

  for (iter = seqsPair.begin(); iter != iterEnd; ++iter) {
    if (flag == true)
    {
      std::cout << " ";
    }
    std::cout << iter->first;
    flag = true;
  }
  std::cout << "\n";

  iter = seqsPair.begin();

  List< int > listSumm;
  Iterator< int > iterList = (*iter).second.begin();
  Iterator< int > iterListEnd = (*iter).second.end();

  size_t seqsPair_size = seqsPair.size();

  int long long summ = 0;
  size_t size = 0;
  flag = false;

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
        size = (*iter).second.size();
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


  return 0;
}
