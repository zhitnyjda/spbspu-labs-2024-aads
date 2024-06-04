#ifndef SORT_FUNCS_HPP
#define SORT_FUNCS_HPP
#include <iostream>
#include <algorithm>
#include <deque>
#include <forward_list>
#include "../common/list.hpp"

namespace psarev
{
  void fillDepots(size_t size, List< int >& list, std::forward_list< int >& fList, std::deque< int >& deque);
  void fillDepots(size_t size, List< double >& list, std::forward_list< double >& fList, std::deque< double >& deque);

  template< typename T >
  std::ostream& outDepot(std::ostream& out, const T& depot);

  template< typename T, typename Compare >
  void makeSorted(std::ostream& out, size_t size, Compare compare);
}

void psarev::fillDepots(size_t size, List< int >& list, std::forward_list< int >& fList, std::deque< int >& deque)
{
  for (size_t i = 0; i < size; ++i)
  {
    list.pushBack(rand() % 100);
    fList.push_back(rand() % 100);
    deque.pushBack(rand() % 100);
  }
}

void psarev::fillDepots(size_t size, List< double >& list, std::forward_list< double >& fList, std::deque< double >& deque)
{
  for (size_t i = 0; i < size; ++i)
  {
    list.pushBack(double(rand() % 1000) / double(rand() % 100));
    fList.push_back(double(rand() % 1000) / double(rand() % 100));
    deque.pushBack(double(rand() % 1000) / double(rand() % 100));
  }
}

template< typename T >
std::ostream& psarev::outDepot(std::ostream& out, const T& depot)
{
  for (auto iter = depot.begin(); iter != depot.end(); iter++)
  {
    out << std::fixed << std::setprecision(1) << *iter;
    if ((std::next(iter) == depot.end())
    {
      out << "\n";
    }
    else
    {
      out << " ";
    }
  }
  return out;
}

template< typename T, typename Compare >
void psarev::makeSorted(std::ostream& out, size_t size, Compare compare)
{
  std::forward_list< T > fList;

  fillDepots(size, list, fList, deque);

  outDepot(out, fList);
  QSort(fList.begin(), fList.end(), compare);
  outDepot(out, fList);

  List< T > list;

  qSort(list.begin(), list.end(), compare);
  outDepot(out, list);
  shellSort(list.begin(), list.end(), compare);
  outDepot(out, list);

  std::deque< T > deque;

  qSort(deque.begin(), deque.end(), compare);
  outDepot(out, deque);
  shellSort(deque.begin(), deque.end(), compare);
  outDepot(out, deque);
  std::sort(deque.begin(), deque.end(), compare);
  outDepot(out, deque);
}

#endif