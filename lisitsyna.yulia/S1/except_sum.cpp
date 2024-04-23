#include "except_sum.hpp"

#include <stdexcept>
#include <limits>

unsigned long long sum(unsigned long long a, unsigned long long b)
{
  if (a > std::numeric_limits< unsigned long long >::max() - b)
  {
    throw std::overflow_error("Overflow!");
  }
  return a + b;
}
