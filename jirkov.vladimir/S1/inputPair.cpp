#include "inputPair.hpp"
#include <limits>
jirkov::List<std::pair<std::string, jirkov::List<size_t>>>jirkov::listInput(std::istream& input)
{
  unsigned long long number = 0;
  const size_t max = std::numeric_limits< size_t >::max();
  std::string string = "";
  jirkov::List< std::pair<std::string, jirkov::List<size_t>>>inputList;
  while(input >> string)
  {
    if (std::isalpha(string[0]))
    {
      inputList.pushBack({ string, jirkov::List<size_t>() });
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
        inputList.tail_->data.second.pushBack(number);
      }
    }
  }
  return inputList;
}

