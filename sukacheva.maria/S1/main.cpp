#include <iostream>
#include "List.hpp"
#include <string>
#include "HelpFunc.hpp"

int main() {
  using namespace sukacheva;
  List< std::pair< std::string, List< size_t > > > newList = listInput(std::cin);
  Iterator<std::pair< std::string, List< size_t > >> it = newList.begin();
  do {
    std::cout << it.node->data.first << " ";
    it++;
  } while (it.node);
  return 0;
}