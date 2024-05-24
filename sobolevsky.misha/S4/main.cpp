#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <functional>
#include <limits>
#include "tree.hpp"
#include "commands.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "missed filename\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "file cannot be opened\n";
    return 1;
  }

  sobolevsky::AVLtree< std::string, sobolevsky::AVLtree< int, std::string, int >,  int > tree;
  sobolevsky::inputFromFile(file, tree);

  sobolevsky::AVLtree< std::string, std::function< void(std::istream &, std::ostream &, sobolevsky::AVLtree< std::string, sobolevsky::AVLtree< int, std::string, int >, int > &) >, int > cmds;

  cmds["print"] = sobolevsky::getPrint;
  cmds["complement"] = sobolevsky::getComplement;
  cmds["intersect"] = sobolevsky::getIntersect;
  cmds["union"] = sobolevsky::getUnion;
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout, tree);
    }
    catch(const std::exception & e)
    {
      sobolevsky::getError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
