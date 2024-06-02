#ifndef SORT_HPP
#define SORT_HPP
#include <utility> //swap
//#include <algorithm> //iter_swap
#include <iterator> //std::distance
#include "compare.hpp"

namespace kovshikov
{
  //для std::forward_list
  template< typename FwdIterator, typename Compare >
  void selectionSort(FwdIterator begin, FwdIterator end, Compare comp);

  template< typename ListIterator, typename Compare >
  void shellSort(ListIterator begin, ListIterator end, Compare comp);
}

template< typename FwdIterator, typename Compare >
void kovshikov::selectionSort(FwdIterator begin, FwdIterator end, Compare comp)
{
  while(begin != end)
  {
    FwdIterator extreme = begin; //extreme
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
  size_t size = std::distance(begin, end);
  for(size_t interval = size / 2; interval > 0; interval /= 2)
  {
    //интревал = количеству подсписков
    for(size_t i = 0; i < interval; i++)
    {
      ListIterator current = std::next(begin, i); //begin + i;
      ListIterator next = std::next(current, interval); //current + interval;
      while(next != std::next(end, i)) //+ i) //тут возможно с адресной арифметикой что то
      {
        ListIterator prev = std::prev(next, interval); //next - interval;
        while(prev != std::next(begin, i - interval)) //)end)//begin + i - interval)
        {
          if(comp(*next, *prev))
          {
            std::swap(*next, *prev);
          }
          prev = std::prev(prev, interval);  //prev - interval;
        }
        next = std::next(next, interval); //next + interval;
      }
    }
  }
}
//у итераторов нет operator++

#endif

