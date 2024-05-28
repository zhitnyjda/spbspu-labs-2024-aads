#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include "../common/tree.hpp"
#include "commands.hpp"
#include "utils.hpp"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "missed some argc\n";
    return 1;
  }
  std::string detourDirection = argv[1];
  std::ifstream file(argv[2]);
  if (!file)
  {
    std::cerr << "file cannot be opened\n";
    return 1;
  }
  sobolevsky::AVLtree< int, std::string, int > tree;
  sobolevsky::inputFromFile(file, tree);
  sobolevsky::AVLtree< std::string, std::function< void(std::ostream &, const sobolevsky::AVLtree< int, std::string, int > &) >, int > cmds;
  cmds["ascending"] = sobolevsky::ascending;
  cmds["descending"] = sobolevsky::descending;
  cmds["breadth"] = sobolevsky::breadth;
  try
  {
    cmds.at(detourDirection)(std::cout, tree);
  }
  catch(const std::out_of_range & e)
  {
    sobolevsky::errorInvalidCommand(std::cout);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  tree.clear();
  cmds.clear();
  return 0;
}
