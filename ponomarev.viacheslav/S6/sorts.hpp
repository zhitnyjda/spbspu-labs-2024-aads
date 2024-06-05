#ifndef SORTS_HPP
#define SORTS_HPP

#include <iostream>

namespace ponomarev
{
  template < typename Iterator, typename Comparator >
  void sortInsertion(Iterator first, Iterator last, Comparator comp)
  {
    for (auto it = first; it != last; ++it)
    {
      auto current = *it;
      auto pos = it;
      while (pos != first && comp(current, *std::prev(pos)))
      {
        *pos = *std::prev(pos);
        if (pos != first) {
          --pos;
        }
      }

      *pos = current;
    }
  }

  template < typename Iterator, typename Comparator >
  void sortShaker(Iterator begin, Iterator end, Comparator comp)
  {
    bool swap = true;
    while (swap)
    {
      swap = false;
      for (auto it = begin; it != std::prev(end); ++it)
      {
        if (comp(*it, *std::next(it)))
        {
          std::iter_swap(std::next(it), it);
          swap = true;
        }
      }

      if (!swap) break;

      swap = false;
      for (auto it = std::prev(end); it != begin; --it)
      {
        if (comp(*it, *std::prev(it)))
        {
          std::iter_swap(it, std::prev(it));
          swap = true;
        }
      }
    }
  }
}
#endif
