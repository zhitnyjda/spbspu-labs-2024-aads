#ifndef SORTS_HPP
#define SORTS_HPP
#include <algorithm>
#include <iostream>
#include <vector>
#include "List.hpp"

namespace sukacheva
{
  template< typename Iterator, typename Comparator >
  void bucketSort(Iterator begin, Iterator end, Comparator cmp);

  template < typename Iterator, typename Comparator >
  void shellSort(Iterator begin, Iterator end, Comparator cmp);
}

template< typename Iterator, typename Comparator >
void sukacheva::bucketSort(Iterator begin, Iterator end, Comparator cmp)
{
  typedef typename Iterator::value_type ValueType;
  if (begin == end || std::distance(begin, end) <= 1)
  {
    return;
  }
  auto minmax = std::minmax_element(begin, end, cmp);
  ValueType minValue = *minmax.first;
  ValueType maxValue = *minmax.second;
  std::size_t bucketCount = std::distance(begin, end);
  std::vector< std::vector< ValueType > > buckets(bucketCount);
  for (auto it = begin; it != end; ++it)
  {
    std::size_t bucketIndex = bucketCount * (*it - minValue) / (maxValue - minValue + 1);
    buckets[bucketIndex].push_back(*it);
  }
  for (size_t i = 0; i < bucketCount; i++)
  {
    bucketSort(buckets[i].begin(), buckets[i].end(), cmp);
    for (size_t j = 0; j < buckets[i].size(); j++)
    {
      *begin = buckets[i][j];
      begin++;
    }
  }
}

template< typename Iterator, typename Comparator >
void sukacheva::shellSort(Iterator begin, Iterator end, Comparator cmp)
{
  typedef typename Iterator::value_type ValueType;
  ValueType n = std::distance(begin, end);
  for (ValueType gap = n / 2; gap > 0; gap /= 2)
  {
    for (Iterator i = std::next(begin, gap); i != end; ++i)
    {
      auto temp = *i;
      Iterator j = i;

      while (std::distance(begin, j) >= gap && cmp(temp, *std::prev(j, gap)))
      {
        *j = *std::prev(j, gap);
        std::advance(j, -gap);
      }
      *j = temp;
    }
  }
}

#endif
