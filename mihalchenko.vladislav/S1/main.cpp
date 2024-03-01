#include <algorithm>
// #include "Iterator.hpp"
// #include "list.hpp"
#include <iostream>
#include <string>
#include <iomanip> // setw

// #include <utility>
#include "list.hpp"

using namespace mihalchenko;

int main()
{
  std::cout << "Hello World" << std::endl;

  // std::pair<std::string, mihalchenko::List<int>> pairs[5];

  List<int> list;
  list.push_back(10);
  list.push_back(123);

  for (auto it = 0; it < list.getSize(); ++it)
  {
    std::cout << list[it] << std::setw(4);
  }

  std::cout << list.begin();

  /*for (auto it = list.begin(); it != list.end(); ++it)
  {
    std::cout<< *it;
  }*/
  return 0;
}
