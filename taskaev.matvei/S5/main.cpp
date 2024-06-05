.#include <iostream>
#include <fstream>
#include <string>
#include "BSTree.hpp"
using namespace taskaev;

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Error: not open file!\n";
    return 1;
  }
  BSTree< size_t, std::string> tree;
  std::ifstream inputs(argv[1]);
  if (!inputs)
  {
    std::cerr << "Error: not open file!\n";
    return 1;
  }
  createTree(inputs, tree);
  BSTree< std::string, std::function< void(BSTree< int, std::string >&) > > cmds;
  cmds.insert("ascending", ascending);
  return 0;
}
