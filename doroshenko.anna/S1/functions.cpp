#include "functions.hpp"

doroshenko::List<std::pair<std::string, doroshenko::List<size_t>>> doroshenko::listInput(std::istream& input)
{
  std::string inputString = "";
  doroshenko::List<std::pair<std::string, doroshenko::List<size_t>>> inputList;
  input >> inputString;
  while (input)
  {
    inputList.pushBack({ inputString, doroshenko::List<size_t>() });
    while (input >> inputString && !std::isalpha(inputString[0]))
    {
      inputList.tail_->data.second.pushBack(std::stoull(inputString));
    }
  }
  return inputList;
}

size_t doroshenko::getMaxSize(doroshenko::List<std::pair<std::string, doroshenko::List<size_t>>>& list)
{
  size_t size = 0;
  size_t maxSize = 0;
  doroshenko::ListIterator< std::pair < std::string, doroshenko::List< size_t >>> iterator = list.begin();
  while (iterator.node)
  {
    size = iterator.node->data.second.getSize();
    maxSize = size > maxSize ? size : maxSize;
    iterator++;
  }
  return maxSize;
}
