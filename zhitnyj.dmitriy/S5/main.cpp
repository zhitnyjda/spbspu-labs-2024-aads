#include <iostream>
#include <functional>
#include <limits>
#include <fstream>
#include <BinarySearchTree.hpp>
#include "TreeTraversal.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Wrong input\n";
    return 1;
  }

  BSTree< long long, std::string > dictionaries;
  BSTree< std::string, std::function< void(BSTree< long long, std::string > &) > > cmds;

  cmds.insert(std::make_pair("ascending", traverseAscending));
  cmds.insert(std::make_pair("descending", traverseDescending));
  cmds.insert(std::make_pair("breadth", traverseBreadth));

  try {
    std::ifstream file(argv[2]);
    if (!file) {
      throw std::runtime_error("Unable to open file");
    }

    long long key;
    std::string value;
    while (file >> key >> value) {
      dictionaries.push(key, value);
    }
    if (!file.eof()) {
      throw std::overflow_error("There must be overflow or underflow!");
    }
  } catch (const std::exception &e) {
    std::cerr << "Error loading file: " << e.what() << "\n";
    return 1;
  }

  std::string command = argv[1];
  auto commandIter = cmds.find(command);
  if (commandIter != cmds.end() && !command.empty()) {
    commandIter->second(dictionaries);
  }
  else if (!command.empty()) {
    invalidCommandError(std::cerr);
    return 1;
  }

  return 0;
}
