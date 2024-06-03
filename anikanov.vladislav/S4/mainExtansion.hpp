#ifndef MAINEXTANSION_HPP
#define MAINEXTANSION_HPP

#include <string>

#include "binarySearchTree.hpp"

namespace anikanov {
  void loadFromFile(const std::string &filename,
                    std::map< std::string, BinarySearchTree< int, std::string, std::less<> > > &dictionaries);
}

#endif
