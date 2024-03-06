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
        firstLine = true;
        break;
      }
      (*iter).second.push_back(num);
    }
    if (std::numeric_limits<int>::max() == num)
    {
      std::cin.clear();
      overflow = true;
    }
  }
  overflow_();
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
  List< int > listSumm;
  if (maxSize != 0)
  {
    Iterator< std::pair< std::string, List< int > > > iter = seqsPair.begin();
    Iterator< std::pair< std::string, List< int > > > iterEnd = seqsPair.end();
    Iterator< int > iterList = (*iter).second.begin();
    Iterator< int > iterListEnd = (*iter).second.end();
    size_t countInSeq = 0;
    int long long summ = 0;

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
          summ == 0 ? std::cout << *iterList : std::cout << " " << *iterList;
          summ += *iterList;
        }
      }
      std::cout << "\n";
      countInSeq++;
      listSumm.push_back(summ);
      summ = 0;
    }
  }


  if (maxSize != 0)
  {
    Iterator< int > iterListSummEnd = listSumm.end();
    size_t count = 0;
    for (Iterator< int > iterListSumm = listSumm.begin(); iterListSumm != iterListSummEnd; ++iterListSumm)
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
  if (overflow == true)
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
