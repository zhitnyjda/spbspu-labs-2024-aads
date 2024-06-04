#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include "binarySearchTree.hpp"
#include "mainExtansion.hpp"

using namespace anikanov;

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  std::map< std::string, BinarySearchTree< int, std::string, std::less<> > > dictionaries;
  loadFromFile(filename, dictionaries);

  std::string command;
  while (std::getline(std::cin, command)) {
    if (command.empty()) {
      command.clear();
      continue;
    }
    char *cstr = new char[command.length() + 1];
    std::strcpy(cstr, command.c_str());

    char *token = std::strtok(cstr, " ");
    std::string cmd(token);

    if (cmd == "print") {
      token = std::strtok(nullptr, " ");
      if (!token) {
        std::cout << "<INVALID COMMAND>" << std::endl;
      } else {
        std::string dictName(token);
        if (dictionaries.count(dictName) == 0) {
          std::cout << "<EMPTY>" << std::endl;
        } else {
          std::cout << dictName << dictionaries[dictName] << std::endl;
        }
      }
    } else if (cmd == "complement" || cmd == "intersect" || cmd == "union") {
      token = std::strtok(nullptr, " ");
      std::string newDict(token);
      token = std::strtok(nullptr, " ");
      std::string dict1(token);
      token = std::strtok(nullptr, " ");
      std::string dict2(token);

      if (dictionaries.count(dict1) == 0 || dictionaries.count(dict2) == 0) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        delete[] cstr;
        continue;
      }

      auto &d1 = dictionaries[dict1];
      auto &d2 = dictionaries[dict2];
      BinarySearchTree< int, std::string, std::less<> > result;

      if (cmd == "complement") {
        for (auto &it: d1) {
          if (!d2.count(it.first)) {
            result.push(it.first, it.second);
          }
        }
      } else if (cmd == "intersect") {
        for (auto &it: d1) {
          if (d2.count(it.first)) {
            result.push(it.first, it.second);
          }
        }
      } else if (cmd == "union") {
        for (auto &it: d1) {
          result.push(it.first, it.second);
        }
        for (auto &it: d2) {
          if (!result.count(it.first)) {
            result.push(it.first, it.second);
          }
        }
      }
      dictionaries[newDict] = std::move(result);
    } else {
      std::cout << "<INVALID COMMAND>" << std::endl;
    }

    delete[] cstr;
  }

  return 0;
}
