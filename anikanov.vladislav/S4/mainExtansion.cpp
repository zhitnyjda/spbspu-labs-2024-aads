#include "mainExtansion.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

void anikanov::loadFromFile(const std::string &filename,
                            std::map< std::string, BinarySearchTree< int, std::string, std::less<> > > &dictionaries)
{
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "Unable to open file: " << filename << std::endl;
    exit(1);
  }

  std::string line;
  while (std::getline(infile, line)) {
    if (line.empty()) continue;

    char *cstr = new char[line.length() + 1];
    std::strcpy(cstr, line.c_str());

    char *token = std::strtok(cstr, " ");
    std::string dictName(token);
    int key;
    std::string value;
    BinarySearchTree< int, std::string, std::less<> > tree;

    while ((token = std::strtok(nullptr, " "))) {
      key = std::stoi(token);
      token = std::strtok(nullptr, " ");
      if (token) {
        value = token;
        tree.push(key, value);
      }
    }

    dictionaries[dictName] = std::move(tree);
    delete[] cstr;
  }
}