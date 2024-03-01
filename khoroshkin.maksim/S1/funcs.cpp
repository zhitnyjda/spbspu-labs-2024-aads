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

  if (allPairs[0].second.isEmpty())
  {
    throw std::logic_error("Empty list");
  }

  for (size_t i = 0; i < maxLength; i++)
  {
    for (auto it = allPairs.begin(); it != allPairs.end(); it++)
    {
      if ((*it).second.getSize() > i)
      {
        out << (*it).second[i];
        (allPairs.next(it) == allPairs.end()) ? out << "\n" : out << " ";
      }
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
