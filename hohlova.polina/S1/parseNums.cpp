#include "parseNums.hpp"

unsigned long long hohlova::ParseNum(const std::string& str, size_t& pos)
{
  auto symbol = static_cast<unsigned char>(str[pos]);
  unsigned long long result = 0;
  while (std::isdigit(symbol))
  {
    result = result * 10 + (symbol - '0');
    if (pos == str.size() - 1)
    {
      ++pos;
      break;
    }
    symbol = static_cast<unsigned char>(str[++pos]);
  }
  return result;
}
