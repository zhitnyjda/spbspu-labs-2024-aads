#include "findSize.hpp"

size_t jirkov::findSize(jirkov::List<std::pair<std::string,jirkov::List<size_t>>>& list)
{
  size_t size = 0;
  size_t maxSize = 0;
  List<std::pair<std::string, jirkov::List<size_t>>>::Iterator iterator = list.begin();
  while (iterator.node)
  {
    size = iterator.node->data.second.getSize();
    maxSize = size > maxSize ? size : maxSize;
    iterator++;
  }
  return maxSize;
}
