#ifndef SORTOPERATIONS_HPP
#define SORTOPERATIONS_HPP

#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
#include <List.hpp>
#include "random.hpp"

namespace zhitnyj {
  template< typename T >
  void printList(const List< T > &list, std::ostream &os) {
    for (auto it = list.begin(); it != list.end(); ++it) {
      os << *it << " ";
    }
    os << std::endl;
  }

  template< typename T >
  void printStdList(const std::list< T > &list, std::ostream &os) {
    for (const auto &elem: list) {
      os << elem << " ";
    }
    os << std::endl;
  }

  template< typename forwardIterator, typename Compare >
  void oddEvenSort(forwardIterator first, forwardIterator last, Compare comp) {
    bool sorted = false;
    while (!sorted) {
      sorted = true;
      for (auto it = first; it != last; ++it) {
        auto next = it;
        ++next;
        if (next != last && comp(*next, *it)) {
          std::swap(*it, *next);
          sorted = false;
        }
        if (next == last) {
          break;
        }
        ++it;
      }
      auto it = first;
      ++it;
      for (; it != last; ++it) {
        auto next = it;
        ++next;
        if (next != last && comp(*next, *it)) {
          std::swap(*it, *next);
          sorted = false;
        }
        if (next == last) {
          break;
        }
        ++it;
      }
    }
  }

  template< typename forwardIterator, typename Compare >
  void insertionSort(forwardIterator first, forwardIterator last, Compare comp) {
    if (first == last) {
      return;
    }
    for (auto it = std::next(first); it != last; ++it) {
      auto key = *it;
      auto j = it;
      while (j != first && comp(key, *std::prev(j))) {
        *j = *std::prev(j);
        --j;
      }
      *j = key;
    }
  }

  template< typename T, typename Compare >
  void stdSort(std::list< T > &lst, Compare comp) {
    lst.sort(comp);
  }

  template< typename T >
  void performSorts(List< T > &singleList, std::list< T > &doubleList, bool ascending, std::ostream &os) {
    std::function< bool(const T &, const T &) > comp;
    if (ascending) {
      comp = std::less< T >();
    }
    else {
      comp = std::greater< T >();
    }

    printList(singleList, os);
    oddEvenSort(singleList.begin(), singleList.end(), comp);
    printList(singleList, os);
    insertionSort(doubleList.begin(), doubleList.end(), comp);
    printStdList(doubleList, os);
    stdSort(doubleList, comp);
    printStdList(doubleList, os);
  }
}

#endif
