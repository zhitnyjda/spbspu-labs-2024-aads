#include "HelpFunc.hpp"
#include <utility>
#include <stddef.h>

sukacheva::List<std::pair<std::string, sukacheva::List<size_t>>> sukacheva::listInput(std::istream& in)
{
  std::string name = "";
  List< size_t > args;
  List< std::pair< std::string, List< size_t > > > resultList;
  in >> name;
  while (in) {
     resultList.pushBack({ name, args });
     while (in >> name && std::isdigit(name[0])) {
       resultList.tail->data.second.pushBack(std::stoul(name));
     }
  }
  return resultList;
}

size_t sukacheva::maxListSize(List< std::pair< std::string, List< size_t > > >& newList) {
  size_t size = 0;
  size_t maxSize = 0;
  Iterator<std::pair< std::string, List< size_t > >> it = newList.begin();
  while (it.node){
    size = it.node->data.second.listSize;
    maxSize = (maxSize < size ? size : maxSize);
    it++;
  }
  return maxSize;
}
