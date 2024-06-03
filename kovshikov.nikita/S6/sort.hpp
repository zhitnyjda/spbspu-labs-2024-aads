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
  int size = std::distance(begin, end);
//  std::cout << "size " << size << "\n";
  for(int interval = size / 2; interval > 0; interval /= 2)
  {
   // std::cout << "interval " << interval << "\n";
    //интревал = количеству подсписков
    for(int i = 0; i < interval; i++)
    {
     // std::cout << "i " << i << "\n";
      ListIterator current = std::next(begin, i); //begin + i;
     // std::cout << "current " << *current << "\n";
      ListIterator next = std::next(current, interval); //current + interval;
     // std::cout << "next " << *next << "\n";
      int count = i + interval;
      while(count < size)//(next != std::next(end, i)) //+ i) //тут возможно с адресной арифметикой что то //НЕПРАВИЛЬНОЕ УСЛОВИЕ ДЛЯ ВАЙЛА
      {
       // std::cout << "while1\n";
       // std::cout << count << "\n";
        ListIterator prev = std::prev(next, interval); //next - interval;
       // std::cout << "prev " << *prev << "\n";
        int count2 = count - interval;
        while(count2 >= 0)//(prev != std::next(begin, i - interval)) //)end)//begin + i - interval)
        {
         // std::cout << "while2\n";
         // std::cout << count2 << "\n";
          if(comp(*next, *prev))
          {
           // std::cout << "if\n";
            std::swap(*next, *prev);
           // std::cout << "swap\n";
          }
          prev = std::prev(prev, interval);  //prev - interval;
          count2 -= interval;
         /* if(prev == std::next(begin, i - interval))
          {
            std::cout << "вышел за диапазон\n";
          }
          else
          {
            std::cout << "prev2 " << *prev << "\n";
          }*/
        }
        next = std::next(next, interval); //next + interval;
        count += interval;
      }
    }
  }
}
//у итераторов нет operator++

#endif

