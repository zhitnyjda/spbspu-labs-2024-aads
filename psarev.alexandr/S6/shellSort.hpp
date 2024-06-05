#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

namespace psarev
{
  template< typename Iter, typename Compare >
  void sortShell(Iter begin, Iter end, Compare compare);
}

template < typename Iter, typename Compare >
void psarev::sortShell(Iter begin, Iter end, Compare compare)
{
  //long long dist = std::distance(begin, end);
  //long long gap = 1;
  //while (gap < dist / 2)
  //{
  //  gap = 2 * gap + 1;
  //}
  //while (gap > 0)
  //{
  //  for (auto i = std::next(begin, gap); i != end; i++)
  //  {
  //    for (auto j = i;
  //      std::distance(begin, j) >= gap && compare(*j, *std::prev(j, gap)); j = std::prev(j, gap))
  //    {
  //      std::iter_swap(j, std::prev(j, gap));
  //    }
  //  }
  //  gap /= 2;
  //}
}

#endif