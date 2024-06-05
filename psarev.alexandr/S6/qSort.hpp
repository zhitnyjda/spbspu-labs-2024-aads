#ifndef Q_SORT_HPP
#define Q_SORT_HPP
#include <iterator>

namespace psarev
{
  template< typename Iter, typename Compare >
  void sortQ(Iter begin, Iter end, Compare compare);

  template< typename Iter, typename Compare >
  Iter splitThat(Iter begin, Iter end, Compare compare);
}

template< typename Iter, typename Compare >
void psarev::sortQ(Iter begin, Iter end, Compare compare)
{
  if (std::distance(begin, end) > 1)
  {
    Iter half = splitThat(begin, end, compare);
    sortQ(begin, half, compare);

    if (split == begin)
    {
      sortQ(++begin, end, compare);
    }
    else
    {
      sortQ(half, end, compare);
    }
  }
}

template< typename Iter, typename Compare >
Iter splitThat(Iter begin, Iter end, Compare compare)
{
  --end;
  while (begin != end)
  {
    if (compare(*begin, *end))
    {
      --end;
    }
    else
    {
      if (std::next(begin) != end)
      {
        std::iter_swap(end, std::next(begin));
        std::iter_swap(begin, std::next(begin));
        ++begin;
      }
      else
      {
        std::iter_swap(begin, std::next(begin));
        return ++begin;
      }
    }
  }
  return begin;
}

#endif