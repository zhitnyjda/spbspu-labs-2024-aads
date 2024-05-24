#ifndef SORTS_HPP
#define SORTS_HPP

#include <functional>
#include <algorithm>
#include <iterator>

namespace miheev
{
  template < typename BidirectIt, typename Comparator >
  void shakeSort(BidirectIt start, BidirectIt finish, Comparator comp);

  template < typename BidirectIt, typename Comparator >
  void shellSort(BidirectIt start, BidirectIt finish, Comparator comp);
}

template < typename BidirectIt, typename Comparator >
void miheev::shakeSort(BidirectIt start, BidirectIt finish, Comparator comp)
{
  BidirectIt second = start;
  BidirectIt first = second++;

  bool swapped = false;
  do
  {
    swapped = false;
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
    while (first != start)
    {
      --first;
      --second;
      if (comp(*second, *first))
      {
        std::iter_swap(first, second);
        swapped = true;
      }
    }
  } while (swapped);
}

template < typename BidirectIt, typename Comparator >
void miheev::shellSort(BidirectIt start, BidirectIt finish, Comparator comp)
{
  for (size_t gap = std::distance(start, finish); gap > 0; gap /= 2)
  {
    BidirectIt cur = std::next(start, gap);
    for (BidirectIt base = cur; ;)
    {

    }
  }
}

#endif
