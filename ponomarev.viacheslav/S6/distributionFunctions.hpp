#include <deque>
#include <forward_list>
#include <algorithm>
#include "list.hpp"

namespace ponomarev
{
  void inputRandomData(List< int > & list, int size)
  {
    for (int i = 0; i < size; ++i)
    {
      list.pushBack((rand() % 1000) - (rand() % 1000));
    }
  }

  void inputRandomData(List< double > & list, int size)
  {
    for (int i = 0; i < size; ++i)
    {
      double firstNum = (double(rand() % 1000) - double(rand() % 1000));
      double secondNum = (double(rand() % 100) / double(rand() % 100));
      list.pushBack(firstNum + secondNum);
    }
  }

  template< typename T, typename Compare >
  void makeSort(std::ostream & out, int size, Compare comp)
  {
    std::forward_list< T > forwardList;
    List< T > firstList;
    inputRandomData(firstList, size);
    std::deque< T > firstDeque;
    std::deque< T > secondDeque;
    List< T > secondList;
    std::copy(firstList.begin(), firstList.end(), std::back_inserter(firstList));
    std::copy(firstList.begin(), firstList.end(), std::back_inserter(firstDeque));
    std::copy(firstList.begin(), firstList.end(), std::back_inserter(secondDeque));
    typename List< T >::Iterator first = firstList.begin();
    typename List< T >::Iterator last = firstList.end();
    while (first != last)
    {
      secondList.pushBack(*first);
      first++;
    }
  }
}
