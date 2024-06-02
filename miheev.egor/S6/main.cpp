#include <iostream>
#include "sorts.hpp"
#include "IOProcessing.hpp"

int main()
{
  using namespace miheev;

  std::deque< int > deq;
  std::list< int > bi;
  fillContainersWithRandom(deq, bi, 8);

  printContainer(std::cout, deq);
  std::cout << '\n';
  printContainer(std::cout, bi);
  std::cout << '\n';

  return 0;
}
