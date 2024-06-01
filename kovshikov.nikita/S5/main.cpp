#include <fstream>
#include <iostream>
#include <string>
#include "BinarySearchTree.hpp"
#include "process.hpp"

int main(int argc, char ** argv)
{
  if(argc != 3)
  {
    std::cerr << "NO SPECIFIED FILE" << "\n";
    return 1;
  }

  std::cout << "START\n"; //

  using namespace kovshikov;
  Tree< int, std::string > tree;
  std::fstream file(argv[2]);

  Tree< std::string, std::function< void(Tree< int, std::string >&) > > commands;
  commands.insert("ascending", getAscending);
  commands.insert("descending", getDescending);
  commands.insert("breadth", getBreadth);

  std::cout << "CURRENT\n"; //
  try
  {
    std::cout << "befor\n"; //
    readData(file, tree);
    std::cout << "after\n"; //
    commands.at(argv[1])(tree);
  }
  catch(const std::exception& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
}
