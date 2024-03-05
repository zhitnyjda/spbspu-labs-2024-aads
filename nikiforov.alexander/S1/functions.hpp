#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>
#include <string>
#include "list.hpp"

namespace nikiforov
{
  template <typename T>
  class Funcs
  {
  public:
    void input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair);
    void outputName_(List< std::pair< std::string, List< T > > >& seqsPair);
    void outputSeqs_(List< std::pair< std::string, List< T > > >& seqsPair);

  private:
    int summ = 0;
  };
}
using namespace nikiforov;

template<typename T>
void Funcs<T>::input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair)
{
  Iterator< std::pair< std::string, List< int > > > iter = seqsPair.begin();
  std::string nameSeq;
  int num = 0;
  bool firstLine = false;

  while (input >> nameSeq)
  {
    if (!firstLine)
    {
      seqsPair.push_back({ nameSeq, {} });
      iter = seqsPair.begin();
    }
    else
    {
      seqsPair.push_back({ nameSeq, {} });
      iter++;
    }

    if (input.peek() == '\n')
    {
      continue;
    }

    while (input >> num)
    {
      if (input.peek() == '\n')
      {
        (*iter).second.push_back(num);
        firstLine = true;
        break;
      }
      (*iter).second.push_back(num);
    }
  }
}

template<typename T>
void Funcs<T>::outputName_(List<std::pair<std::string, List<T>>>& seqsPair)
{
  Iterator< std::pair< std::string, List< int > > > iter = seqsPair.begin();
  Iterator< std::pair< std::string, List< int > > > iterEnd = seqsPair.end();
  size_t countNames = seqsPair.size();

  for (iter = seqsPair.begin(); iter != iterEnd; ++iter)
  {
    if (countNames == 1)
    {
      std::cout << iter->first;
    }
    else
    {
      std::cout << iter->first << " ";
    }
    countNames--;
  }
}

template<typename T>
void Funcs<T>::outputSeqs_(List<std::pair<std::string, List<T>>>& seqsPair)
{
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
    std::cout << "\n";
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
}

#endif
