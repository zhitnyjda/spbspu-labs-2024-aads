#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <utility>
#include <limits>
#include "AVLTree.hpp"
#include "commands.hpp"

int main(int argc, char *argv[])
{
  using namespace mihalchenko;
  if (argc != 2)
  {
    std::cerr << "The filename parameter is not set\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  return 0;
}
