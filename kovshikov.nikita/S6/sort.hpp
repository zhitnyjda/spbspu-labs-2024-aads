#ifndef SORT_HPP
#define SORT_HPP
#include <utility>
#include <iterator>
#include "compare.hpp"
#include <iostream>
#include "random.hpp"

namespace kovshikov
{
  template< typename FwdIterator, typename Compare >
  void selectionSort(FwdIterator begin, FwdIterator end, Compare comp);

  template< typename ListIterator, typename Compare >
  void shellSort(ListIterator begin, ListIterator end, Compare comp);

  template< typename Iterator, typename Compare >
  void bubbleSort(Iterator begin, Iterator end, Compare comp);

//тип будет определен в main.cpp
  template< typename Deque, typename FwdList, typename List >
  void sort(std::string comp, std::string strSize, Deque& deque, FwdList& fwdList, List& list);
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

template< typename Deque, typename FwdList, typename List >
void kovshikov::sort(std::string comp, std::string strSize, std::string type, Deque& deque, FwdList& fwdList, List& list);
{
  long long size = std::stoll(strSize);
  if(type == "ints")
  {
    getRandomInt(list, fwdList, deque, size);
  }
  else
  {
    getRandomFloat(list, fwdList, deque, size);
  }
  if(comp == "ascending")
  {
    Ascending ascending;
    selectionSort(fwdList.begin(), fwdList.end(), ascending);
    selectionSort(deque.begin(), deque.end(), ascending);
    shellSort(list.begin(), list.end(), ascending);
    shellSort(deque.begin(), deque.end(), ascending);
    bubbleSort(list.begin(), list.end(), ascending);
    bubbleSort(deque.begin(), deque.end(), ascending);
  }
  else
  {
    Descending descending;
    selectionSort(fwdList.begin(), fwdList.end(), descending);
    selectionSort(deque.begin(), deque.end(), descending);
    shellSort(list.begin(), list.end(), descending);
    shellSort(deque.begin(), deque.end(), descending);
    bubbleSort(list.begin(), list.end(), descending);
    bubbleSort(deque.begin(), deque.end(), descending);
  }
}

#endif
