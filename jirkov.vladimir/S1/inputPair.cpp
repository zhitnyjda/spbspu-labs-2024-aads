#include "inputPair.hpp"
#include <limits>

jirkov::List<std::pair<std::string, jirkov::List<size_t>>>jirkov::inputPair(std::istream& input)
{
  size_t number = 0;
  const size_t max = std::numeric_limits< size_t >::max();
  std::string string = "";
  jirkov::List< std::pair<std::string, jirkov::List<size_t>>>inputPair;
  while(input >> string)
  {
    if (std::isalpha(string[0]))
    {
      inputPair.pushBack({ string, jirkov::List<size_t>() });
    }
    else
    {
      number = std::stoull(string);
      if (number > max)
      {
        throw std::overflow_error("overflow error");
      }
      else
      {
        inputPair.back().second.pushBack(number);
      }
    }
  }
  return inputPair;
}
