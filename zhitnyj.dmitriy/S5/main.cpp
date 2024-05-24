#include <iostream>
#include <functional>
#include <limits>
#include <fstream>
#include "BinarySearchTree.hpp"
#include "TreeTraversal.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Wrong input\n";
    return 1;
  }

  BSTree< long long, std::string > dictionaries;
  BSTree< std::string, std::function< void(BSTree< long long, std::string > &) > > cmds;

  cmds.insert(std::make_pair("ascending", traverseAndPrintAscending));
  cmds.insert(std::make_pair("descending", traverseAndPrintDescending));
  cmds.insert(std::make_pair("breadth", traverseAndPrintBreadth));

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
    invalidCommandWarning(std::cout);
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  
  return 0;
}
