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
  std::cout << "\n";
  for (size_t i = 0; i < maxListSize(newList); i++) {
    it = newList.begin();
    while (it.node) {
      if (it.node->data.second[i]) {
        std::cout << it.node->data.second[i]->data << " ";
      }
      it++;
    }
    std::cout << "\n";
  }
  return 0;
}
