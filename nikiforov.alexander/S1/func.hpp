#ifndef FUNC_HPP
#define FUNC_HPP
#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"

namespace nikiforov
{
  template <typename T>
  void input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair, bool overflow);

  template <typename T>
  void outputName_(List< std::pair< std::string, List< T > > >& seqsPair);

  template <typename T>
  List<T> outputSeqs_(List< std::pair< std::string, List< T > > >& seqsPair);

  template <typename T>
  void outputSumms(List<T>& listSumm);

  void overflow_();
  size_t max(const size_t first_param, const size_t second_param);
}

template <typename T>
void nikiforov::input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair, bool overflow)
{
  Iterator< std::pair< std::string, List< unsigned long long > > > iter = seqsPair.begin();
  std::string nameSeq;
  unsigned long long num = 0;
  bool firstLine = false;

  while (input >> nameSeq)
  {
    if (!firstLine)
    {
      seqsPair.push_back({ nameSeq, {} });
      iter = seqsPair.begin();
      firstLine = true;
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
        break;
      }
      (*iter).second.push_back(num);
    }
  }
}

template<typename T>
void nikiforov::outputName_(List<std::pair<std::string, List<T>>>& seqsPair)
{
  List< unsigned long long > listSumm;
  if (maxSize != 0)
  {
    Iterator< std::pair< std::string, List< unsigned long long > > > iter = seqsPair.begin();
    Iterator< std::pair< std::string, List< unsigned long long > > > iterEnd = seqsPair.end();
    Iterator< unsigned long long > iterList = (*iter).second.begin();
    Iterator< unsigned long long > iterListEnd = (*iter).second.end();
    size_t countInSeq = 0;
    unsigned long long summ = 0;

    while (countInSeq < maxSize)
    {
      for (iter = seqsPair.begin(); iter != iterEnd; ++iter)
      {
        iterList = (*iter).second.begin();
        for (size_t i = 0; i < countInSeq; i++)
        {
          if (iterList != nullptr)
          {
            iterList++;
          }
        }
        if (iterList != nullptr)
        {
          iter == seqsPair.begin() ? std::cout << *iterList : std::cout << " " << *iterList;
          if ((std::numeric_limits<unsigned long long>::max() - summ) > *iterList)
          {
            summ += *iterList;
          }
        }
      }
      std::cout << "\n";
      countInSeq++;
      if (!overflow)
      {
        listSumm.push_back(summ);
      }
      summ = 0;
    }
  }
}
#endif
