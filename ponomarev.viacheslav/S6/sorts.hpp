#ifndef SORTS_HPP
#define SORTS_HPP

#include <algorithm>
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
  void sortShaker(Iterator first, Iterator last, Comparator comp)
  {
    last--;
    while (first != last)
    {
      Iterator left = first;
      Iterator right = last;

      while (left != right)
      {
        if (comp(*std::next(left), *left))
        {
          std::iter_swap(left, std::next(left));
          last = left;
        }
        left++;
      }

      if (left == first)
      {
        break;
      }

      while (right != first)
      {
        if (comp(*right, *std::prev(right)))
        {
          std::iter_swap(right, std::prev(right));
        }
        right--;
      }

      first++;
    }
  }
}

#endif
