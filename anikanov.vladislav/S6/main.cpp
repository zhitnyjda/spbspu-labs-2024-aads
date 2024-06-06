#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include <random>
#include <deque>
#include <forward_list>
#include <list.hpp>

#include "mainExtension.hpp"

int main(int argc, char *argv[])
{
  using namespace anikanov;

  if (argc != 4) {
    printUsingError(std::cerr);
    return 1;
  }

  bool ascending = std::string(argv[1]) == "ascending";
  auto intComparator = ascending
                       ? std::function< bool(int, int) >(std::less< int >())
                       : std::function< bool(int, int) >(std::greater< int >());
  auto floatComparator = ascending
                         ? std::function< bool(float, float) >(std::less< float >())
                         : std::function< bool(float, float) >(std::greater< float >());

  auto typeSelected = std::string(argv[2]);
  size_t size;

  try {
    size = std::stoi(argv[3]);
  } catch (std::invalid_argument &e) {
    printInvalidType(std::cerr);
    return 1;
  }

  if (size < 1) {
    printInvalidCount(std::cerr);
    return 1;
  }

  std::srand(static_cast< unsigned >(std::time(0)));

  if (typeSelected == "ints") {
    std::forward_list< int > fwd;
    List< int > list;
    std::deque< int > deq;

    generateRandomData(fwd, list, deq, size);
    printContainer(std::cout, fwd);
    applySort(fwd, list, deq, intComparator, std::cout);
  } else if (typeSelected == "floats") {
    std::forward_list< float > fwd;
    List< float > list;
    std::deque< float > deq;

    generateRandomData(fwd, list, deq, size);
    printContainer(std::cout, fwd);
    applySort(fwd, list, deq, floatComparator, std::cout);
  } else {
    printInvalidType(std::cerr);
    return 1;
  }
}
