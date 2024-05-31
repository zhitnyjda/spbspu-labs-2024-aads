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

  using namespace kovshikov;
  Tree< int, std::string > tree;
  std::fstream file(argv[2]);
  readData(file, tree);

  Tree< std::string, std::function< void(Tree< int, std::string >&) > > commands;
  commands.insert("ascending", getAscending);
  commands.insert("descending", getDescending);
  commands.insert("breadth", getBreadth);

  try
  {
    commands.at(argv[2])(tree);
  }
  catch(const std::out_of_range& e)
  {
    std::cerr << "NO MATCH COMMANDS" << "\n";
    return 1;
  }
}
