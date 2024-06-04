#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP
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
  }
}
#endif
