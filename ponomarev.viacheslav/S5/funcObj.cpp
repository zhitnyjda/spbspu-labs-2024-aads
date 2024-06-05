#include "funcObj.hpp"
#include <limits>
#include <stdexcept>

void ponomarev::Key_summ::operator()(const std::pair< int, std::string > & value)
{
  bool checkOverflow = (value.first > 0) && (sum > (std::numeric_limits< int >::max() - value.first));
  if (checkOverflow)
  {
    throw std::out_of_range("Error: owerflow");
  }

  bool checkUnderflow = (value.first < 0) && (sum < (std::numeric_limits< int >::min() - value.first));
  if (checkUnderflow)
  {
    throw std::out_of_range("Error: underflow");
  }

  sum += value.first;
  valueRes += (" " + value.second);
}
