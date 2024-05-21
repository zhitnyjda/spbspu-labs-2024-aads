#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include <string>
#include <map>
#include <functional>
#include "BinarySearchTree.hpp"

void loadTreeFromFile(const std::string &filename, BSTree< std::string, BSTree< long long, std::string > > &dicts);
void handlePrint(BSTree< std::string, BSTree< long long, std::string > > &dicts);
void handleComplement(BSTree< std::string, BSTree< long long, std::string > > &dicts);
void handleIntersect(BSTree< std::string, BSTree< long long, std::string > > &dicts);
void handleUnion(BSTree< std::string, BSTree< long long, std::string > > &dicts);
void invalidCommandWarning(std::ostream &out);
void emptyCommandWarning(std::ostream &out);

#endif
