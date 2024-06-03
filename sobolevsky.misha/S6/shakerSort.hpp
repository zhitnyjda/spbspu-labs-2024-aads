#ifndef SHAKERSORT_HPP
#define SHAKERSORT_HPP

#include <algorithm>
#include <iterator>

namespace sobolevsky
{
  template < typename Iterator, typename Comparator >
  void shakerSort(Iterator begin, Iterator end, Comparator comp)
  {
    bool flag = true;
    while (flag)
    {
      flag = false;
      Iterator left = begin;
      Iterator right = end;

      while (left != right)
      {
        if (comp(*std::next(left), *left))
        {
          std::iter_swap(left, std::next(left));
          flag = true;
        }
        left++;
      }

      right--;

      while (right != begin)
      {
        if (comp(*right, *std::prev(right)))
        {
          std::iter_swap(right, std::prev(right));
          flag = true;
        }
        right--;
      }

      begin++;
    }
  }
}

#endif
