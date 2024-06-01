#ifndef SORT_HPP
#define SORT_HPP
#include <utility> //swap
//#include <algorithm> //iter_swap
#include "compare.hpp"

namespace kovshikov
{
  //для std::forward_list
  template< typename FwdIterator, typename Compare >
  void selectionSort(FwdIterator begin, FwdIterator end, Compare comp);
}

template< typename FwdIterator, typename Compare >
void kovshikov::selectionSort(FwdIterator begin, FwdIterator end, Compare comp)
{
  while(begin != end)
  {
    FwdIterator extreme = begin; //extreme
    FwdIterator current = begin;
    while(current != end)
    {
      if(comp(*current, *extreme))
      {
        extreme = current;
      }
      current++;
    }
    std::swap(*extreme, *begin);
  //std::iter_sawp(extreme, current);
    begin++;
  }
}

#endif

