#ifndef TREEPROCESS_HPP
#define TREEPROCESS_HPP
#include <string>
#include "BinarySearchTree.hpp"

namespace kovshikov
{
  void readData(std::istream& in, Tree< std::string, Tree< long long, std::string > >& allTree);
  void createTree(Tree< std::string, Tree< long long, std::string > >& allTree, std::string dictionary);
  bool isDigit(std::string str);
}

#endif
