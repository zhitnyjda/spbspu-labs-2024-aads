#include "funcs.hpp"
#include <limits>
#include <stdexcept>

using namespace khoroshkin;

void khoroshkin::printResult(std::ostream & out, List< std::pair< std::string, List< int > > > & allPairs, size_t maxLength)
{
  for (auto it = allPairs.begin(); it != allPairs.end(); ++it)
  {
    out << (*it).first;
    allPairs.next(it) == allPairs.end() ? std::cout << "\n" : std::cout << " ";
  }

  for (size_t i = 0; i < maxLength; i++)
  {
    bool emptyLine = true;
    for (auto it = allPairs.begin(); it != allPairs.end(); it++)
    {
      if ((*it).second.getSize() > i)
      {
        out << (*it).second[i];
        (allPairs.next(it) == allPairs.end() || maxLength - 1 != i) ? std::cout << " " : std::cout << "\n";
        emptyLine = false;
      }
    }
    if (!emptyLine && i != maxLength - 1)
    {
      out << "\n";
    }
  }

  for (size_t i = 0; i < maxLength; i++)
  {
    long long sum = 0;
    for (auto it = allPairs.begin(); it != allPairs.end(); it++)
    {
      if ((*it).second.getSize() > i)
      {
        if (std::numeric_limits<long long>::max() - sum < (*it).second[i])
        {
          throw std::overflow_error("overflow!");
        }
        sum += (*it).second[i];
      }
    }
    out << sum;
    (i + 1 == maxLength) ? out << "\n" : out << " ";
  }
}
