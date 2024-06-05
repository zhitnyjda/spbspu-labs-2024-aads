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
    void operator()(const std::pair< const int, std::string >& keyValue)
    {
      int max = std::numeric_limits< int >::max();
      int min = std::numeric_limits< int >::min();
      if (max - keyValue.first < result)
      {
        throw std::overflow_error("<OVERFLOW>\n");
      }
      else if (min - keyValue.first > result)
      {
        throw std::overflow_error("<UNDERFLOW>\n");
      }
      result += keyValue.first;
      values.push(keyValue.second);
    }
    int result = 0;
    Queue< std::string > values;
  };
}

#endif
