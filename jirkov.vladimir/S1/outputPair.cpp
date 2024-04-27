#include "outputPair.hpp"
#include "findSize.hpp"
#include <limits>

void jirkov::outputPair(jirkov::List<std::pair<std::string, jirkov::List<size_t>>> list)
{
  List< std::pair< std::string, jirkov::List< size_t > > >::Iterator iterator = list.begin();
  size_t maxSize = findSize(list);
  jirkov::List< size_t >::Iterator locIt = nullptr;
  List< size_t > sums;
  List< size_t >::Iterator it;
  const size_t maximum = std::numeric_limits< size_t >::max();
  size_t sum = 0;
  bool overflowError = false;
  if (!list.empty())
  {
    while (iterator != list.end())
    {
      if (iterator != list.begin())
      {
        std::cout << " ";
      }
      std::cout << iterator->first;
      iterator++;
    }
    std::cout << "\n";
    for (size_t index = 0; index < maxSize; index++)
    {
      iterator = list.begin();
      while (iterator != list.end())
      {
        if (iterator->second[index] != nullptr)
        {
          if (sum > 0)
          {
            std::cout << " ";
          }
          locIt = iterator->second[index];
          std::cout << *locIt;
          if (maximum - sum < *locIt)
          {
            overflowError = true;
            std::cout << "\n";
            throw std::overflow_error("overflow error");
          }
          else
          {
            sum = sum + *locIt;
          }
        }
        iterator++;
      }
      if (!overflowError)
      {
        sums.pushBack(sum);
      }
      sum = 0;
      overflowError = false;
      std::cout << "\n";
    }

    it = sums.begin();
    if (sums.empty())
    {
      std::cout << 0;
    }
    else
    {
      while (it != sums.end())
      {
        if (it != nullptr)
        {
          if (it != sums.begin())
          {
            std::cout << " ";
          }
          std::cout << *it;
        }
        it++;
      }
    }
    std::cout << "\n";
  }
  else
  {
    std::cout << 0 << "\n";
  }
}
