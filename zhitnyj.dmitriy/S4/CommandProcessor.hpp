#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include <string>
#include <map>
#include <functional>
#include "BinarySearchTree.hpp"

void loadTreeFromFile(const std::string &filename, bsTree< std::string, bsTree< long long, std::string > > &dicts);
void handlePrint(bsTree< std::string, bsTree< long long, std::string > > &dicts);
void handleComplement(bsTree< std::string, bsTree< long long, std::string > > &dicts);
void handleIntersect(bsTree< std::string, bsTree< long long, std::string > > &dicts);
void handleUnion(bsTree< std::string, bsTree< long long, std::string > > &dicts);
void displayEmptyWarning(std::ostream &out);
void displayInvalidCommand(std::ostream &out);

#endif
