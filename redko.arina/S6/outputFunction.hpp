#ifndef OUTPUTFUNCTIONS_HPP
#define OUTPUTFUNCTIONS_HPP
#include <ostream>
#include <iomanip>
#include <deque>
#include <list>
#include "list.hpp"
#include "bucketSort.hpp"
#include "quickSort.hpp"

namespace redko
{
  template< typename It >
  void printSorted(std::ostream & out, It first, It last)
  {
    while (first != last)
    {
      out << *first;
      out << (++first == last ? '\n' : ' ');
    }
  }

  template< typename T, typename Compare >
  void sortData(std::ostream & out, int size, Compare comp)
  {
    srand(time(0));

    redko::List< T > forwardList{};
    for (auto i = 0; i < size; ++i)
    {
      forwardList.pushBack(T(rand()) / 10);
    }

    std::list< T > firstList(size);
    std::copy_n(forwardList.cbegin(), size, firstList.begin());
    std::list< T > secondList(size);
    std::copy_n(forwardList.cbegin(), size, secondList.begin());
    std::deque< T > firstDeque(size);
    std::copy_n(forwardList.cbegin(), size, firstDeque.begin());
    std::deque< T > secondDeque(size);
    std::copy_n(forwardList.cbegin(), size, secondDeque.begin());
    std::deque< T > thirdDeque(size);
    std::copy_n(forwardList.cbegin(), size, thirdDeque.begin());

    out << std::fixed << std::setprecision(1);
    redko::printSorted(out, forwardList.begin(), forwardList.end());

    redko::sortBucket(forwardList.begin(), forwardList.end(), comp);
    redko::sortBucket(firstList.begin(), firstList.end(), comp);
    redko::sortQuick(secondList.begin(), secondList.end(), comp);
    redko::sortBucket(firstDeque.begin(), firstDeque.end(), comp);
    redko::sortQuick(secondDeque.begin(), secondDeque.end(), comp);
    std::sort(thirdDeque.begin(), thirdDeque.end(), comp);

    redko::printSorted(out, forwardList.begin(), forwardList.end());
    redko::printSorted(out, firstList.begin(), firstList.end());
    redko::printSorted(out, secondList.begin(), secondList.end());
    redko::printSorted(out, firstDeque.begin(), firstDeque.end());
    redko::printSorted(out, secondDeque.begin(), secondDeque.end());
    redko::printSorted(out, thirdDeque.begin(), thirdDeque.end());
  }
}

#endif
