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
      list.pushBack((rand() % 1000));
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

  template< typename It >
  std::ostream & printData(std::ostream & out, It first, It last)
  {
    while (first != last)
    {
      out << *first;
      out << (++first == last ? '\n' : ' ');
    }
    return out;
  }

  template< typename T, typename Compare >
  void makeSort(std::ostream & out, int size, Compare comp)
  {
    std::forward_list< T > forwardList;
    List< T > firstList;
    List< T > secondList;
    inputRandomData(firstList, size);
    std::deque< T > firstDeque;
    std::deque< T > secondDeque;
    std::deque< T > thirdDeque;

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

    printData(out, firstList.begin(), firstList.end());

    sortShaker(forwardList.begin(), forwardList.end(), comp);
    sortShaker(firstList.begin(), firstList.end(), comp);
    sortInsertion(secondList.begin(), secondList.end(), comp);
    sortShaker(firstDeque.begin(), firstDeque.end(), comp);
    sortInsertion(secondDeque.begin(), secondDeque.end(), comp);
    std::sort(thirdDeque.begin(), thirdDeque.end(), comp);

    printData(out, forwardList.begin(), forwardList.end());
    printData(out, firstList.begin(), firstList.end());
    printData(out, secondList.begin(), secondList.end());
    printData(out, firstDeque.begin(), firstDeque.end());
    printData(out, secondDeque.begin(), secondDeque.end());
    printData(out, thirdDeque.begin(), thirdDeque.end());
  }
}
