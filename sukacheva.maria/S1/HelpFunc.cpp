#include "HelpFunc.hpp"
#include <string>

sukacheva::List<std::pair<std::string, sukacheva::List<size_t>>> sukacheva::listInput(std::istream& in)
{
  std::string name = "";
  List< size_t > args;
  List< std::pair< std::string, List< size_t > > > resultList;
  in >> name;
  while (in) {
     resultList.pushBack({ name, args });

     while (in >> name && std::isdigit(name[0])) {
       resultList.head->data.second.pushBack(std::stoul(name));
     }
  }
  return resultList;
}