#ifndef SORT_HPP
#define SORT_HPP
#include <utility> //swap
//#include <algorithm> //iter_swap
#include <iterator> //std::distance
#include "compare.hpp"
#include <iostream>

namespace kovshikov
{
  //для std::forward_list
  template< typename FwdIterator, typename Compare >
  void selectionSort(FwdIterator begin, FwdIterator end, Compare comp);

  template< typename ListIterator, typename Compare >
  void shellSort(ListIterator begin, ListIterator end, Compare comp);

  template< typename Iterator, typename Compare >
  void bubbleSort(Iterator begin, Iterator end, Compare comp);
}

template< typename FwdIterator, typename Compare >
void kovshikov::selectionSort(FwdIterator begin, FwdIterator end, Compare comp)
{
  while(begin != end)
  {
    FwdIterator extreme = begin;
    FwdIterator current = begin;
    while(current != end)
    {
      if(comp(*current, *extreme))
      {
        extreme = current;
      }
      current++;
    }
    std::swap(*extreme, *begin);
  //std::iter_sawp(extreme, current);
    begin++;
  }
}

template< typename ListIterator, typename Compare >
void kovshikov::shellSort(ListIterator begin, ListIterator end, Compare comp)
{
  int size = std::distance(begin, end);
  for(int interval = size / 2; interval > 0; interval /= 2)
  {
    for(int i = 0; i < interval; i++)
    {
      ListIterator current = std::next(begin, i);
      ListIterator next = std::next(current, interval);
      int indexNext = i + interval;
      while(indexNext < size)
      {
        ListIterator prev = std::prev(next, interval);
        int indexPrev = indexNext - interval;
        while(indexPrev >= 0)
        {
          if(comp(*next, *prev))
          {
            std::swap(*next, *prev);
          }
          prev = std::prev(prev, interval);
          indexPrev -= interval;
        }
        next = std::next(next, interval);
        indexNext += interval;
      }
    }
  }
}

template< typename Iterator, typename Compare >
void kovshikov::bubbleSort(Iterator begin, Iterator end, Compare comp)
{
  bool isSort = false;
  bool firstIteration = true;
  while(isSort != false || firstIteration == true)
  {
    isSort = false;
    firstIteration = false;
    Iterator current = begin;
    Iterator prev = current;
    current++;
    while(current != end)
    {
      if(comp(*current, *prev))
      {
        isSort = true;
        std::swap(*current, *prev);
      }
      prev = current;
      current++;
    }
  }
}

#endif
