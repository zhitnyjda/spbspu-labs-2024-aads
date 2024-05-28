#ifndef UTILS_HPP
#define UTILS_HPP

#include "../common/tree.hpp"

namespace sobolevsky
{
  void inputFromFile(std::istream &in, sobolevsky::AVLtree< int, std::string, int > &data);
  void errorInvalidCommand(std::ostream &out);
  void errorEmpty(std::ostream &out);
}

#endif
