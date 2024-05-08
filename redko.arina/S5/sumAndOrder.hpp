#ifndef SUMANDORDER_HPP
#define SUMANDORDER_HPP
#include <utility>
#include <string>
#include <limits>
#include "queue.hpp"

namespace redko
{
  struct SumAndOrder
  {
    void operator()(const std::pair< int, std::string > & value)
    {
      if (sum > std::numeric_limits< int >::max() - value.first)
      {
        throw std::overflow_error("Error: unable to calculate the sum due to overflow");
      }
      sum += value.first;
      valueOrder.push(value.second);
    }
    int sum = 0;
    Queue< std::string > valueOrder;
  };
}

#endif
