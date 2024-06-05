#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>
#include <fstream>
#include "BSTree.hpp"
#include "Queue.hpp"

namespace taskaev
{
  void createTree(std::istream& in, BSTree<int, std::string>& tree);
  bool numbers(const std::string& str);
  void ascending(BSTree< int, std::string >& tree);
  void descending(BSTree< int, std::string >& tree);
  void breadth(BSTree< int, std::string >& tree);
  void errorEmpty(std::ostream& out);
}

#endif
