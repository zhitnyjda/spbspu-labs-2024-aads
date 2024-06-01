#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <string>
#include "AVLtree.hpp"

namespace mihalchenko
{
  std::string resiveString(std::string &inputStr, size_t &pos, bool flag);
  using typeParam = mihalchenko::AVLTree<std::string, mihalchenko::AVLTree<long long, std::string>>;
  void print(typeParam &AVLTree);
  void intersect(typeParam &AVLTree);
  void unionAVL(typeParam &AVLTree);
  void complement(typeParam &AVLTree);
  void insertDataToTree(std::ifstream &input, typeParam &TreeAndLeaves, std::string &inputStr);
}

#endif
