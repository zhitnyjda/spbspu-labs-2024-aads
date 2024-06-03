#include <iostream>
#include "sort.hpp"
#include "random.hpp"
#include <iomanip>

int main()
{
  std::cout << std::fixed << std::setprecision(3);
  using namespace kovshikov;
  std::list< int > listInt;
  std::forward_list< int > fwdListInt;
  std::deque< int > dequeInt;
  std::list< float > listFloat;
  std::forward_list< float > fwdListFloat;
  std::deque< float > dequeFloat;

  size_t size = 10;

  getRandomInt(listInt, fwdListInt, dequeInt, size);
  getRandomFloat(listFloat, fwdListFloat, dequeFloat, size);

  printConteiner(listInt, std::cout);
  printConteiner(fwdListInt, std::cout);
  printConteiner(dequeInt, std::cout);
  printConteiner(listFloat, std::cout);
  printConteiner(fwdListFloat, std::cout);
  printConteiner(dequeFloat, std::cout);
}
