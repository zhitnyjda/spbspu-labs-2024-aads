#include <iostream>
#include <functional>
#include "BinarySearchTree.hpp"
#include "CommandProcessor.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Wrong input\n";
    return 1;
  }

  BinarySearchTree< std::string, BinarySearchTree< long long, std::string > > dictionaries;
  BinarySearchTree< std::string, std::function< void(BinarySearchTree< std::string, BinarySearchTree< long long, std::string> > &) > > commands;

  commands.insert(std::make_pair("print", handlePrint));
  commands.insert(std::make_pair("complement", handleComplement));
  commands.insert(std::make_pair("intersect", handleIntersect));
  commands.insert(std::make_pair("union", handleUnion));

  auto invalidCommandWarning = std::bind(displayWarning, std::ref(std::cerr), "<INVALID COMMAND>\n");

  try {
    loadTreeFromFile(argv[1], dictionaries);
  } catch (const std::exception &e) {
    std::cerr << "Error loading file: " << e.what() << "\n";
    return 1;
  }

  while (!std::cin.eof()) {
    std::string command;
    std::cin >> command;

    auto commandIter = commands.find(command);
    if (commandIter != commands.end() && !command.empty()) {
      commandIter->second(dictionaries);
    }
    else if (!command.empty()) {
      invalidCommandWarning();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
