#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <string>
#include "../common/tree.hpp"

namespace sobolevsky
{
  void ascending(std::ostream &out, const sobolevsky::AVLtree< int, std::string, int > &tree);
  void descending(std::ostream &out, const sobolevsky::AVLtree< int, std::string, int > &tree);
  void breadth(std::ostream &out, const sobolevsky::AVLtree< int, std::string, int > &tree);
}

#endif
