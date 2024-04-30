#ifndef TASK_HPP
#define TASK_HPP
#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"

namespace zheleznyakov
{
  void processTask(std::ostream&, List< std::pair< std::string, List< unsigned long long > > >&);
  void processTitles(std::ostream&, List< std::pair< std::string, List< unsigned long long > > >&);
  void processSequences(std::ostream&, List< std::pair< std::string, List< unsigned long long > > >&);
  size_t findMaxSequenceLength(List< std::pair< std::string, List< unsigned long long > > >&);
}

void zheleznyakov::processTask(std::ostream& out, List< std::pair < std::string, List< unsigned long long > > >& pairs)
{
  processTitles(out, pairs);
  processSequences(out, pairs);
}

void zheleznyakov::processTitles(std::ostream& out, List< std::pair< std::string, List< unsigned long long > > >& pairs)
{
  using list_type = std::pair< std::string, List< unsigned long long > >;
  List< list_type >::Iterator iter(pairs.begin());
  while (iter != pairs.end())
  {
    out << (*iter).first;
    iter++;
    if (iter == pairs.end()) out << "\n";
    else out << " ";
  }
}

void zheleznyakov::processSequences(std::ostream& out, List< std::pair < std::string, List< unsigned long long > > >& pairs)
{
  const size_t maxSequenceLength = findMaxSequenceLength(pairs);
  zheleznyakov::List< unsigned long long > sums;
  unsigned long long currentSum = 0;
  bool overflowFlag = false;
  for (size_t i = 0; i < maxSequenceLength; i++)
  {
    currentSum = 0;
    for (size_t j = 0; j < pairs.getSize(); j++)
    {
      if (pairs[j].second.getSize() > i)
      {
        if (currentSum != 0)
        {
          out << ' ';
        }
        out << pairs[j].second[i];
        if (currentSum > (std::numeric_limits< unsigned long long >::max() - pairs[j].second[i]))
        {
          overflowFlag = true;
        }
        else
        {
          currentSum += pairs[j].second[i];
        }
      }
    }
    sums.pushBack(currentSum);
    out << '\n';
  }
  if (overflowFlag)
  {
    throw std::overflow_error("Got overflow while calculating sums");
  }
  if (sums.getSize() == 0)
  {
    out << 0 << '\n';
  }
  else
  {
    for (size_t i = 0; i < sums.getSize(); i++)
    {
      out << sums[i] << (i == sums.getSize() - 1 ? '\n' : ' ');
    }
  }
}

size_t zheleznyakov::findMaxSequenceLength(List< std::pair < std::string, List< unsigned long long > > >& pairs)
{
  size_t maxSequenceLength = 0;
  for (size_t i = 0; i < pairs.getSize(); i++)
  {
    maxSequenceLength = std::max(maxSequenceLength, pairs[i].second.getSize());
  }
  return maxSequenceLength;
}
#endif
