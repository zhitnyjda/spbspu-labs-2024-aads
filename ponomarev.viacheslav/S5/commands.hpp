#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <string>
#include "binarySearchTreeAVL.hpp"

namespace ponomarev
{
  using tree_t = ponomarev::BSTree< int, std::string, int >;

  void makeInput(std::istream & in, tree_t & data);

  void makeAscending(std::ostream & out, tree_t & data);
  void makeDescending(std::ostream & out, tree_t & data);
  void makeBreadth(std::ostream & out, tree_t & data);
}

#endif
