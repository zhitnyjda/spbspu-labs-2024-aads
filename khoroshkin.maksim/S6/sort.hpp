#ifndef SORT_HPP
#define SORT_HPP

#include <functional>
#include <algorithm>
#include <utility>
#include <iterator>
#include <list.hpp>

namespace khoroshkin
{
  template< typename ForwardIt, typename Compare >
  void selectionSort(ForwardIt first, ForwardIt last, Compare comp);

  template< typename ForwardItIt, typename Compare >
  void mergeRuns(ForwardItIt first1, ForwardItIt last1, ForwardItIt first2, ForwardItIt last2, Compare comp);

  template< typename ForwardItIt, typename Compare >
  void timSort(ForwardItIt first, ForwardItIt last, Compare comp);

  int getMinrun(int N);

  template< typename BiderectIt, typename Compare >
  void shellSort(BiderectIt first, BiderectIt last, Compare comp);

  template< typename T >
  std::ostream & outContainer(std::ostream & out, const T & container);
}

template< typename ForwardIt, typename Compare >
void khoroshkin::selectionSort(ForwardIt first, ForwardIt last, Compare comp)
{
  if (comp(1,2))
  {
    for (auto i = first; i != last; ++i)
    {
      std::iter_swap(i, std::min_element(i, last));
    }
  }
  else
  {
    for (auto i = first; i != last; ++i)
  {
    std::iter_swap(i, std::max_element(i, last));
  }
  }
}

template< typename ForwardIt, typename Compare >
void khoroshkin::mergeRuns(ForwardIt first1, ForwardIt last1, ForwardIt first2, ForwardIt last2, Compare comp)
{
  List< int > fRange{ first1, last1 };
  List< int > sRange{ first2, last2 };
  auto fIt = fRange.begin();
  auto sIt = sRange.begin();
  while (fIt != fRange.end() && sIt != sRange.end())
  {
    if (comp(*fIt, *sIt))
    {
      *first1 = *fIt;
      first1++;
      fIt++;
    }
    else
    {
      *first1 = *sIt;
      first1++;
      sIt++;
    }
  }
  for (;fIt != fRange.end(); ++fIt)
  {
    *first1 = *fIt;
    first1++;
  }
  for (;sIt != sRange.end(); ++sIt)
  {
    *first1 = *sIt;
    first1++;
  }
}

template< typename ForwardIt, typename Compare >
void khoroshkin::timSort(ForwardIt first, ForwardIt last, Compare comp)
{
  size_t size = std::distance(first, last);
  size_t minrun = getMinrun(size);
  auto savedFirst = first;
  while (first != last)
  {
    auto sortFrom = first;
    for (size_t i = 0; first != last && i < minrun; ++i)
    {
      first++;
    }
    selectionSort(sortFrom, first, comp);
  }
  while (savedFirst != last)
  {
    auto mergeFrom = savedFirst;
    for (size_t i = 0; savedFirst != last && i < minrun; ++i)
    {
      savedFirst++;
    }
    auto mergeTo = savedFirst;
    auto secondMergeFrom = savedFirst;
    for (size_t i = 0; savedFirst != last && i < minrun; ++i)
    {
      savedFirst++;
    }
    mergeRuns(mergeFrom, mergeTo, secondMergeFrom, savedFirst, comp);
  }
}

int khoroshkin::getMinrun(int N)
{
  int addition = 0;
  while (N >= 64)
  {
    addition |= (N & 1);
    N >>= 1;
  }
  return N + addition;
}

template< typename BiderectIt, typename Compare >
void khoroshkin::shellSort(BiderectIt first, BiderectIt last, Compare comp)
{
  size_t size = std::distance(first, last);
  size_t range = 1;
  while (range < size / 3)
  {
    range = 3 * range + 1;
  }
  while (range >= 1)
  {
    for (auto i = std::next(first, range); i != last; ++i)
    {
      for (auto j = i; std::distance(first, j) >= range && comp(*j, *std::prev(j, range)); j = std::prev(j, range))
      {
        std::swap(*j, *std::prev(j, range));
      }
    }
    range /= 3;
  }
}

template< typename T >
std::ostream & khoroshkin::outContainer(std::ostream & out, const T & container)
{
  for (auto it = container.begin(); it != container.end(); it++)
  {
    out << std::fixed << std::setprecision(1) << *it;
    out << ((std::next(it) == container.end()) ? "\n" : " ");
  }
  return out;
}

#endif
