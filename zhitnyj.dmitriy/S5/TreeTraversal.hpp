#ifndef TREETRAVERSAL_HPP
#define TREETRAVERSAL_HPP

#include <BinarySearchTree.hpp>

void traverseAndPrintAscending(const BSTree< long long, std::string > &tree);
void traverseAndPrintDescending(const BSTree< long long, std::string > &tree);
void traverseAndPrintBreadth(const BSTree< long long, std::string > &tree);
void invalidCommandWarning(std::ostream &out);
void emptyCommandWarning(std::ostream &out);

#endif
