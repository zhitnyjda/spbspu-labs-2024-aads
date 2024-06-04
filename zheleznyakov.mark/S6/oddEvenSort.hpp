#ifndef ODD_EVEN_SORT_HPP
#define ODD_EVEN_SORT_HPP
#include <algorithm>
#include <iterator>

namespace zheleznyakov
{
  namespace sorts
  {
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
