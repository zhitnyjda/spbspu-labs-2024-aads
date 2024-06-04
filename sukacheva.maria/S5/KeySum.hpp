#ifndef KEYSUM_HPP
#define KEYSUM_HPP
#include <utility>
#include <string>
#include "Queue.hpp"

namespace sukacheva
{
  struct KeySum
  {
    void operator()(const std::pair< const int, std::string >& keyValue)
    {
      result += keyValue.first;
      values.push(keyValue.second);
    }
    int result = 0;
    Queue< std::string > values;
  };
}

#endif
