#ifndef IO_FUNCTIONS_HPP
#define IO_FUNCTIONS_HPP

#include <iosfwd>
#include "binarySearchTreeAVL.hpp"

namespace ponomarev
{
  void inputFromFile(std::istream & in, BinarySearchTree< std::string, BinarySearchTree< int, std::string, int >, int > & data);
  std::ostream & printInvalidCommandMessage(std::ostream & out);
}

#endif
