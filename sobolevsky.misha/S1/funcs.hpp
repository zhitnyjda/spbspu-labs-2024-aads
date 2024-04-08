#ifndef FUNCS_HPP
#define FUNCS_HPP
#include <limits>
#include <iostream>
#include "list.hpp"

namespace sobolevsky
{
  template< typename T >
  void output(const List< T > list, size_t maxlen, size_t length)
  {
    bool isOverflow = false;
    sobolevsky::List< unsigned long long > lastList;
    size_t sumInts = 0;
    for (size_t i = 0; i < maxlen; i++)
    {
      sumInts = 0;
      bool first = true;
      sobolevsky::Iterator< sobolevsky::List< unsigned long long > > iter2(list.head);
      for (size_t j = 0; j < length; j++)
      {
        if (i < iter2.currNode->data.size)
        {
          if (first)
          {
            std::cout << iter2.currNode->data[i]->data;
            first = false;
          }
          else
          {
            std::cout << " " << iter2.currNode->data[i]->data;
          }

          if (iter2.currNode->data[i]->data > (std::numeric_limits< unsigned long long >::max() - sumInts))
          {
            isOverflow = true;
          }
          else
          {
            sumInts += iter2.currNode->data[i]->data;
          }
        }
        ++iter2;
      }
      lastList.pushBack(sumInts, " ");
      std::cout << "\n";

      if (isOverflow)
      {
        throw std::overflow_error("overflow!\n");
      }

      for (size_t i = 0; i < lastList.size; i++)
      {
        std::cout << lastList[i]->data;
        if (i != (lastList.size - 1))
        {
          std::cout << " ";
        }
      }
      std::cout << "\n";
    }
  }
}

#endif