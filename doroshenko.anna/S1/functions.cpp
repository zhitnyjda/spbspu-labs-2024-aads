#include "functions.hpp"
#include <limits>

doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > doroshenko::listInput(std::istream& input)
{
  std::string inputString = "";
  doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > inputList;
  unsigned long long readNumber = 0;
  const size_t maximum = std::numeric_limits< size_t >::max();
  while(input >> inputString)
  {
    if (std::isalpha(inputString[0]))
    {
      inputList.pushBack({ inputString, doroshenko::List< size_t >() });
    }
    else
    {
      readNumber = std::stoull(inputString);
      if (readNumber > maximum)
      {
        throw std::overflow_error("overflow error");
      }
      else
      {
        inputList.tail_->data.second.pushBack(readNumber);
      }
    }
  }
  return inputList;
}

size_t doroshenko::getMaxSize(doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > >& list)
{
  size_t size = 0;
  size_t maxSize = 0;
  doroshenko::ListIterator< std::pair< std::string, doroshenko::List< size_t > > > iterator = list.begin();
  while (iterator.node)
  {
    size = iterator.node->data.second.getSize();
    maxSize = size > maxSize ? size : maxSize;
    iterator++;
  }
  return maxSize;
}
