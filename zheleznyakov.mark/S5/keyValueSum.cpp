#include "keyValueSum.hpp"
#include <stdexcept>
#include <limits>

zheleznyakov::KeyValueSum::KeyValueSum():
  keySum_(0),
  valueSum_("")
{}

void zheleznyakov::KeyValueSum::operator()(std::pair< long long, std::string > & pair)
{
  const long long minLimit = std::numeric_limits< long long >::min();
  const long long maxLimit = std::numeric_limits< long long >::max();
  
  long long toKeyAdd = pair.first;
  std::string toValueAdd = pair.second;

  if (toKeyAdd > 0 && maxLimit - keySum_ < toKeyAdd)
  {
    throw std::overflow_error("");
  }

  if (minLimit + keySum_ > toKeyAdd)
  {
    throw std::overflow_error("");
  }

  keySum_ += toKeyAdd;
  valueSum_ += ' ' + toValueAdd;
}
