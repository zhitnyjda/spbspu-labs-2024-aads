#ifndef TASK_HPP
#define TASK_HPP
#include <iostream>
#include <string>
#include "list.hpp"

namespace zheleznyakov
{
  void processTask(std::ostream &, List<std::pair<std::string, List<unsigned long long>>>);
  template <typename T>
  List<T> sum(zheleznyakov::List<zheleznyakov::List<unsigned long long>> rows);
}

void zheleznyakov::processTask(std::ostream &out, List<std::pair<std::string, List<unsigned long long>>> pairs)
{
  if (pairs.isEmpty())
  {
    throw std::logic_error("List is empty");
  }
  if (pairs[0].second.isEmpty())
  {
    throw std::logic_error("List is empty");
  }

  for (size_t i = 0; i < pairs.getSize(); i++)
  {
    out << pairs[i].first << (i < pairs.getSize() - 1 ? " " : "\n");
  }

  size_t maxSequenceLength = 0;
  for (size_t i = 0; i < pairs.getSize(); i++)
  {
    maxSequenceLength = std::max(maxSequenceLength, pairs[i].second.getSize());
  }
  zheleznyakov::List<zheleznyakov::List<unsigned long long>> rows;
  for (size_t i = 0; i < maxSequenceLength; i++)
  {
    zheleznyakov::List<unsigned long long> iterationElements;
    for (size_t j = 0; j < pairs.getSize(); j++)
    {
      try
      {
        iterationElements.pushBack(pairs[j].second[i]);
      }
      catch (const std::out_of_range &e)
      {
      }
    }
    rows.pushBack(iterationElements);
  }

  zheleznyakov::List<unsigned long long> sums;
  for (size_t i = 0; i < rows.getSize(); i++)
  {
    unsigned long long currentSum = 0;
    for (size_t j = 0; j < rows[i].getSize(); j++)
    {
      currentSum += rows[i][j];
      out << rows[i][j] << (j == rows[i].getSize() - 1 ? '\n' : ' ');
    }
    sums.pushBack(currentSum);
  }

  for (size_t i = 0; i < sums.getSize(); i++)
  {
    out << sums[i] << (i == sums.getSize() - 1 ? '\n' : ' ');
  }
}
#endif
