#include <iostream>
#include <string>
#include <list>
#include <List.hpp>
#include "sortOperations.hpp"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: ./lab [ascending|descending] [ints|floats] [size]" << std::endl;
    return 1;
  }

  bool ascending = std::string(argv[1]) == "ascending";
  bool isInt = std::string(argv[2]) == "ints";
  size_t size = std::stoi(argv[3]);

  if (isInt) {
    zhitnyj::List< int > singleList;
    std::list< int > doubleList;
    zhitnyj::generateNumbers(singleList, doubleList, size, true);
    zhitnyj::performSorts(singleList, doubleList, ascending, std::cout);
  }
  else {
    zhitnyj::List< float > singleList;
    std::list< float > doubleList;
    zhitnyj::generateNumbers(singleList, doubleList, size, false);
    zhitnyj::performSorts(singleList, doubleList, ascending, std::cout);
  }

  return 0;
}
