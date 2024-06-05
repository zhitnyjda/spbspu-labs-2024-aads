#ifndef KEYSUM_HPP
#define KEYSUM_HPP
#include <utility>
#include <string>
#include <limits>
#include "Queue.hpp"

namespace sukacheva
{
  struct KeySum
  {
    void operator()(const std::pair< const long long int, std::string >& keyValue)
    {
      long long max = std::numeric_limits< long long >::max();
      long long min = std::numeric_limits< long long >::min();
      if (keyValue.first > 0 && keyValue.first > max - result)
      {
        throw std::overflow_error("<OVERFLOW>\n");
      }
      else if (keyValue.first < 0 && keyValue.first < min - result)
      {
        throw std::underflow_error("<UNDERFLOW>\n");
      }
      result += keyValue.first;
      values.push(keyValue.second);
    }
    int result = 0;
    Queue< std::string > values;
  };
}

#endif
