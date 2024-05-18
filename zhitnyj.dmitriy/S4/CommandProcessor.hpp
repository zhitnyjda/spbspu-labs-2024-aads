#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include <string>
#include <map>
#include <functional>
#include "BinarySearchTree.hpp"

void loadTreeFromFile(const std::string &filename, BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries);
void handlePrint(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries);
void handleComplement(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries);
void handleIntersect(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries);
void handleUnion(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dictionaries);
void displayWarning(std::ostream &out, const std::string &message);

#endif
