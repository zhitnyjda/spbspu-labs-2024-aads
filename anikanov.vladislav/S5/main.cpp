#include <iostream>

#include "mainExtansion.hpp"

int main(int argc, char *argv[])
{
  using namespace anikanov;
  if (argc != 3) {
    printInvalidUsage(std::cerr, argv);
    return 1;
  }

  std::cout << "hi!\n";
}
