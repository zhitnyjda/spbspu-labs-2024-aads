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
      if (keyValue.first > 0 && result > max - keyValue.first)
      {
        throw std::overflow_error("<OVERFLOW>\n");
      }
      else if (keyValue.first < 0 && result < min - keyValue.first)
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
