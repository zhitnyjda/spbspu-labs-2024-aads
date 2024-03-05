#ifndef DIVIDE_FUNCS
#define DIVIDE_FUNCS
#include "list.hpp"
#include <iostream>
#include <string>

namespace psarev
{
  std::string getOrd(std::string& line);
  int getDigit(std::string& line);

  template < typename T >
  void outSums(List< T >& sums);

  template < typename T >
  void outOrds(List< std::pair< std::string, List< T > > >& lines);
}

template < typename T >
void psarev::outSums(List< T >& sums)
{
  if (sums.getSize() == 0)
  {
    std::cout << 0;
  }
  else
  {
    Iterator< T > iterSums = sums.begin();
    for (size_t i = 0; i < sums.getSize(); i++)
    {
      if (i != 0)
      {
        std::cout << ' ';
      }
      std::cout << *iterSums;
      iterSums++;
    }
  }
  std::cout << '\n';
}

template < typename T >
void psarev::outOrds(List< std::pair< std::string, List< T > > >& lines)
{
  Iterator< std::pair< std::string, List< T > > > iterLine = lines.begin();
  for (size_t i = 0; i < lines.getSize(); i++)
  {
    std::cout << (*iterLine).first;
    iterLine++;
    if (i < (lines.getSize() - 1))
    {
      std::cout << ' ';
    }
    else
    {
      std::cout << '\n';
    }
  }
}

#endif
