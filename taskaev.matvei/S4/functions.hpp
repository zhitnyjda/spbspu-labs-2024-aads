#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <fstream>
#include "BSTree.hpp"
#include <string>

namespace taskaev
{
  using Tree = BSTree< std::string, BSTree< size_t, std::string > >;
  using SubTree = BSTree< size_t, std::string >;
  using Iterator = SubTree::Iterator;

  void createTree(std::istream& in, Tree& tree);

  void print(Tree& tree);
  void helpPrint(SubTree& tree, Iterator it, Iterator end);

  void complement(Tree& tree);
  void findcomplement(SubTree& two, SubTree& one, SubTree& tree);

  void intersect(Tree& tree);

  void unions(Tree& tree);
  SubTree mergeTrees(SubTree& treeOne, SubTree& treeTwo);

  void errorInvalid(std::ostream& out);
  void errorEmpty(std::ostream& out);
}

#endif
