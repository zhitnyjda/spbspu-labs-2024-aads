#ifndef DATAFUNCTIONS_HPP
#define DATAFUNCTIONS_HPP
#include <string>
#include "binarySearchTree.hpp"

namespace redko
{
  int cutKey(std::string & str);
  void print(BSTree< std::string, BSTree <int, std::string > > & dataSets);
  void complement(BSTree< std::string, BSTree <int, std::string > > & dataSets);
  void intersect(BSTree< std::string, BSTree <int, std::string > > & dataSets);
  void unite(BSTree< std::string, BSTree <int, std::string > > & dataSets);
}

#endif
