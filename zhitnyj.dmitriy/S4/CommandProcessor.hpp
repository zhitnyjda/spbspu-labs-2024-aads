#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include <string>
#include <map>
#include <functional>
#include "BinarySearchTree.hpp"

void loadTreeFromFile(const std::string &filename, BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dicts);
void handlePrint(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dicts);
void handleComplement(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dicts);
void handleIntersect(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dicts);
void handleUnion(BinarySearchTree< std::string, BinarySearchTree< long long, std::string>> &dicts);
void displayWarning(std::ostream &out, const std::string &message);

#endif
