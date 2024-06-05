#ifndef MAINEXTANSION_HPP
#define MAINEXTANSION_HPP

#include <iosfwd>
#include <string>
#include <binarySearchTree.hpp>

namespace anikanov {
  bool loadTreeFromFile(std::string &fileName, BinarySearchTree< int, std::string, std::less<> > &tree);
  void printInvalidUsage(std::ostream &os, char *argv[]);
  void printInvalidMode(std::ostream &os);
  void printEmpty(std::ostream &os);
}

#endif
