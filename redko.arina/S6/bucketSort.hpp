#ifndef BUCKETSORT_HPP
#define BUCKETSORT_HPP
#include <algorithm>
#include <vector>

namespace redko
{
  template < class It >
  void sortBucket(It first, It last, bool ascending = true)
  {
    auto minmax = std::minmax_element(first, last);
    const int num = 5;
    if (std::distance(first, last) > 1 && *(minmax.first) != *(minmax.second))
    {
      int range = *(minmax.second) - *(minmax.first);
      std::vector< typename It::value_type > buckets[num];
      for (It curr = first; curr != last; ++curr)
      {
        if (*curr == *(minmax.second))
        {
          buckets[num - 1].push_back(*curr);
        }
        else
        {
          int index = ((*curr - *(minmax.first)) * num / range);
          buckets[index].push_back(*curr);
        }
      }
      It curr = first;
      if (ascending == true)
      {
        for (int i = 0; i < num; ++i)
        {
          sortBucket(buckets[i].begin(), buckets[i].end());
          for (auto j = buckets[i].begin(); j != buckets[i].end(); ++j)
          {
            *curr = *j;
            ++curr;
          }
        }
      }
      else
      {
        for (int i = num - 1; i >= 0; --i)
        {
          sortBucket(buckets[i].begin(), buckets[i].end(), false);
          for (auto j = buckets[i].begin(); j != buckets[i].end(); ++j)
          {
            *curr = *j;
            ++curr;
          }
        }
      }
    }
  }
}

#endif
