#include <iostream>
#include <utility>
#include <string>
#include "list.hpp"

int main()
{
  std::cout << "input string:\n";
  std::string cur;
  while (!std::cin.eof() && std::cin)
  {
    std::cin >> cur;
    std::cout << cur << '\n';
  }
  return 0;
}

