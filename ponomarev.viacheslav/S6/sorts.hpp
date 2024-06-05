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
  void sortShaker(Iterator begin, Iterator end, Comparator comp)
  {
    end--;
    while (begin != end)
    {
      Iterator left = begin;
      Iterator right = end;

      while (left != right)
      {
        if (comp(*std::next(left), *left))
        {
          std::iter_swap(left, std::next(left));
          end = left;
        }
        left++;
      }

      if (left == begin)
      {
        break;
      }

      while (right != begin)
      {
        if (comp(*right, *std::prev(right)))
        {
          std::iter_swap(right, std::prev(right));
        }
        right--;
      }

      begin++;
    }
  }
}

#endif
