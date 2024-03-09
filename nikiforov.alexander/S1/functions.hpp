#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>
#include <string>
#include <limits>
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
    void overflow_();
    size_t max(const size_t first_param, const size_t second_param);

  private:
    size_t maxSize = 0;
    bool overflow = false;
  };
}
using namespace nikiforov;

template<typename T>
void Funcs<T>::input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair)
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
void Funcs<T>::outputName_(List<std::pair<std::string, List<T>>>& seqsPair)
{
  Iterator< std::pair< std::string, List< unsigned long long > > > iter = seqsPair.begin();
  Iterator< std::pair< std::string, List< unsigned long long > > > iterEnd = seqsPair.end();
  size_t countNames = seqsPair.size();

  for (iter = seqsPair.begin(); iter != iterEnd; ++iter)
  {
    if (countNames == 1)
    {
      std::cout << iter->first << "\n";
    }
    else
    {
      std::cout << iter->first << " ";
    }
    maxSize = max(maxSize, iter->second.size());
    countNames--;
  }
}

template<typename T>
void Funcs<T>::outputSeqs_(List<std::pair<std::string, List<T>>>& seqsPair)
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
          else
          {
            overflow = true;
          }
        }
      }
      std::cout << "\n";
      countInSeq++;
      listSumm.push_back(summ);
      summ = 0;
    }
    overflow_();
  }

  if (maxSize != 0)
  {
    Iterator< unsigned long long > iterListSummEnd = listSumm.end();
    size_t count = 0;
    for (Iterator< unsigned long long > iterListSumm = listSumm.begin(); iterListSumm != iterListSummEnd; ++iterListSumm)
    {
      count++;
      listSumm.size() == count ? std::cout << *iterListSumm : std::cout << *iterListSumm << " ";
    }
    std::cout << "\n";
  }
  else
  {
    std::cout << 0 << "\n";
  }
}

template<typename T>
void nikiforov::Funcs<T>::overflow_()
{
  if (overflow)
  {
    throw std::overflow_error("Error: overflow!");
  }
}

template<typename T>
size_t nikiforov::Funcs<T>::max(const size_t first_param, const size_t second_param)
{
  return first_param > second_param ? first_param : second_param;
}

#endif