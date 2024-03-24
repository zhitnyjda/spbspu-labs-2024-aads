#include <iostream>
#include "List.hpp"
#include <string>
#include "HelpFunc.hpp"
#include <exception>

int main() {
  using namespace sukacheva;
  try {
    List< std::pair< std::string, List< size_t > > > newList = listInput(std::cin);
    Iterator<std::pair< std::string, List< size_t > >> it = newList.begin();
    if (maxListSize(newList) == 0) {
      if (!newList.empty())
      {
        do {
          std::cout << it.node->data.first;
          if (it.node->next) {
            std::cout << " ";
          }
          it++;
        } while (it.node);
        std::cout << "\n";
      }
      std::cout << "0\n";
    }
    else {
      do {
        std::cout << it.node->data.first;
        if (it.node->next) {
          std::cout << " ";
        }
        it++;
      } while (it.node);
      std::cout << "\n";
      List<size_t> sumOfArgs;
      for (size_t i = 0; i < maxListSize(newList); i++) {
        it = newList.begin();
        size_t sum = 0;
        while (it.node) {
          if (it.node->data.second[i])
          {
            std::cout << it.node->data.second[i]->data;
            sum += it.node->data.second[i]->data;
            if (sum > 0) {
              std::cout << " ";
            }
          }
          it++;
        }
        std::cout << "\n";
        sumOfArgs.pushBack(sum);
      }
      Iterator<size_t> itSum = sumOfArgs.begin();
      do {
        std::cout << itSum.node->data;
        if (itSum.node->next) {
          std::cout << " ";
        }
        itSum++;
      } while (itSum.node);
      std::cout << "\n";
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
