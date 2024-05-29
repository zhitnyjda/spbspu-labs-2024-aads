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

  using secondPar = AVLTree<std::string, AVLTree<long long, std::string>>;
  AVLTree<std::string, std::function<void(secondPar & AVLTree)>> commands{};
  commands.insert("print", print);
  commands.insert("union", unionAVL);
  commands.insert("intersect", intersect);
  commands.insert("complement", complement);

  return 0;
}
