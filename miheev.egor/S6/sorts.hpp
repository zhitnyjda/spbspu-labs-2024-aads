#ifndef SORTS_HPP
#define SORTS_HPP

#include <functional>
#include <algorithm>

namespace miheev
{
  template < typename BidirectIt, typename Comparator >
  void shakeSort(BidirectIt start, BidirectIt finish, Comparator comp);

  template < typename BidirectIt, typename Comparator >
  void shellSort(BidirectIt start, BidirectIt finish, Comparator comp);
}

template < typename BidirectIt, typename Comparator >
void shakeSort(BidirectIt start, BidirectIt finish, Comparator comp)
{
  bool swapped = false;
  BidirectIt second = start;
  BidirectIt first = second++;

  do
  {
    while (second != finish)
    {
      if (comp(*second, *first))
      {
        std::iter_swap(first, second);
        swapped = true;
      }
      ++first;
      ++second;
    }
    while (first)
    {
      --first;
      --second;
      if (comp(*second, *first))
      {
        std::iter_swap(first, second);
        swapped = true;
      }
    }
  } while (swapped)
}


#endif
