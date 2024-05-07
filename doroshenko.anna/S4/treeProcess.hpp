#ifndef TREE_PROCESS_HPP
#define TREE_PROCESS_HPP
#include <iostream>
#include <string>
#include "BinarySearchTree.hpp"

namespace doroshenko
{
  void strToTree(std::string expression, BST< std::string, BST< long long, std::string > >& result);
  void inputTree(std::istream& input, BST< std::string, BST< long long, std::string > >& treeOfDicts);
  void print(BST< std::string, BST< long long, std::string > >& treeOfDicts);
  void complement(BST< std::string, BST< long long, std::string > >& treeOfDicts);
  void intersect(BST< std::string, BST< long long, std::string > >& treeOfDicts);
  void unify(BST< std::string, BST< long long, std::string > >& treeOfDicts);
}

#endif
