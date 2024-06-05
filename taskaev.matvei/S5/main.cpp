#include <iostream>
#include <fstream>
#include <string>
#include "BSTree.hpp"

int main(int argc, char ** argv)
{
  using namespace taskaev;
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
  std::string name = argv[1];
  createTree(inputs, tree);
  BSTree< std::string, std::function< void(BSTree< int, std::string >&) > > cmds;
  cmds.insert("ascending", ascending);
  cmds.insert("descending", descending);
  cmds.insert("breadth", breadth);

  try
  {
    cmds.at(name)(tree);
  }
  catch(...)
  {
    std::cerr << "ERROR!\n";
    return 1;
  }
  return 0;
}
