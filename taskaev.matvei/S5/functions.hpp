#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>
#include <fstream>
#include "BSTree.hpp"
#include "Queue.hpp"

namespace taskaev
{
  void createTree(std::istream& in, BSTree<int, std::string>& tree); // взял из S4 и переделал чуть чуть
  void ascending(BSTree< int, std::string >& tree);
  void descending(BSTree< int, std::string >& tree);
}

#endif
