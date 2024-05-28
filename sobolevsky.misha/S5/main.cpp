#include <iostream>
#include <fstream>
#include <functional>
#include "../common/tree.hpp"
#include "commands.hpp"
#include "errorsANDinput.hpp"

int main(long long argc, char *argv[])
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
  sobolevsky::AVLtree< long long, std::string, long long > tree;
  sobolevsky::inputFromFile(file, tree);
  if (tree.isEmpty())
  {
    sobolevsky::errorEmpty(std::cout);
    return 0;
  }
  sobolevsky::AVLtree< std::string, std::function< void(std::ostream &, const sobolevsky::AVLtree< long long, std::string, long long > &) >,
  long long > cmds;
  cmds["ascending"] = sobolevsky::ascending;
  cmds["descending"] = sobolevsky::descending;
  cmds["breadth"] = sobolevsky::breadth;
  try
  {
    cmds.at(detourDirection)(std::cout, tree);
  }
  catch(const std::out_of_range & e)
  {
    sobolevsky::errorInvalidCommand(std::cerr);
    tree.clear();
    cmds.clear();
    return 1;
  }
  catch(const std::overflow_error & e)
  {
    sobolevsky::errorOverflow(std::cerr);
    tree.clear();
    cmds.clear();
    return 1;
  }
  catch(const std::underflow_error & e)
  {
    sobolevsky::errorUnderflow(std::cerr);
    tree.clear();
    cmds.clear();
    return 1;
  }
  tree.clear();
  cmds.clear();
  return 0;
}
