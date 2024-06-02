#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
#include <string>

namespace taskaev
{
  void createTree(std::istream& in, BSTree<std::string, BSTree<size_t, std::string>>& tree);
  void print(BSTree< std::string, BSTree< size_t, std::string > >& tree);
  void printTree(const BSTree<size_t, std::string>& tree, BSTree<size_t, std::string>::Iterator iterator, BSTree<size_t, std::string>::Iterator end);

  void complement(BSTree<std::string, BSTree<size_t, std::string>>& tree);
  void findComplementItems(BSTree<size_t, std::string>& sourceTree, BSTree<size_t, std::string>& otherTree, BSTree<size_t, std::string>& newTree);

  void intersect(BSTree<std::string, BSTree<size_t, std::string>>& tree);

  void unions(BSTree<std::string, BSTree<size_t, std::string>>& tree);
  BSTree<size_t, std::string> mergeTrees(BSTree<size_t, std::string>& treeOne, BSTree<size_t, std::string>& treeTwo);

  void errorInvalid(std::ostream& out);
  void errorEmpty(std::ostream& out);
}

#endif
