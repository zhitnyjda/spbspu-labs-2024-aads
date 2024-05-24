#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "tree.hpp"

namespace sobolevsky
{
  void inputFromFile(std::istream &in, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data);
  void getError(std::ostream &out, std::string text);
  void getPrint(std::istream &in, std::ostream &out, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data);
  void getComplement(std::istream &in, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data);
  void getIntersect(std::istream &in, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data);
  void getUnion(std::istream &in, AVLtree< std::string, AVLtree< int, std::string, int >,  int > &data);
}

#endif
