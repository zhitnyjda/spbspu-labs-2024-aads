#ifndef SORTS_HPP
#define SORTS_HPP
#include <algorithm>
#include <iterator>

namespace zheleznyakov
{
  namespace sorts
  {
    template < typename Iterator, typename Comparator >
    void insertion(Iterator begin, Iterator end, Comparator cmp)
    {
      for (auto it = begin; it != end; ++it)
      {
        auto current = *it;
        auto pos = it;
        while (pos != begin && cmp(current, *std::prev(pos)))
        {
          *pos = *std::prev(pos);
          if (pos != begin) {
            --pos;
          }
        }
        *pos = current;
      }
    }

    template < typename Iterator, typename Comparator >
    void oddEven(Iterator begin, Iterator end, Comparator cmp)
    {
      bool isSorted = false;

      while (!isSorted)
      {
        isSorted = true;
        Iterator next = std::next(begin);
        for (Iterator it = next; it != end && it != std::prev(end); std::advance(it, 2))
        {
          if (it != std::prev(end) && cmp(*it, *std::next(it)))
          {
            std::iter_swap(it, std::next(it));
            isSorted = false;
          }
        }
        for (Iterator it = begin; it != end && it != std::prev(end); std::advance(it, 2))
        {
          if (cmp(*it, *std::next(it)))
          {
            std::iter_swap(it, std::next(it));
            isSorted = false;
          }
        }
      }
    }
  }
}
#endif
