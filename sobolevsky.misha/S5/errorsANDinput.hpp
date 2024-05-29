#ifndef ERRORSANDINPUT_HPP
#define ERRORSANDINPUT_HPP

#include <tree.hpp>

namespace sobolevsky
{
  void inputFromFile(std::istream &in, sobolevsky::AVLtree< long long, std::string, long long > &data);
  void errorInvalidCommand(std::ostream &out);
  void errorEmpty(std::ostream &out);
  void errorOverflow(std::ostream &out);
  void errorUnderflow(std::ostream &out);
}

#endif
