#include <fstream>
#include <iostream>
#include <string>
#include "BinarySearchTree.hpp"
#include "treeProcess.hpp"

int main(int argc, char ** argv )
{
  if(argc != 2)
  {
    std::cerr << "NO FILE SPECIFIED" << "\n";
    return 1;
  }

  using namespace kovshikov;
  Tree< std::string, Tree< size_t, std::string > > allTree;
  std::ifstream file(argv[1]);
  readData(file, allTree);

  Tree< std::string, std::function < void(Tree< std::string, Tree< size_t, std::string > >&) > > commands;
  commands.insert("print", print);
  commands.insert("complement", getComplement);
  commands.insert("intersect", getIntersect);
  commands.insert("union", getUnion);

  std::string command;
  while(std::cin >> command)
  {
    try
    {
      commands.at(command)(allTree);
    }
    catch(const std::out_of_range& error)
    {
      outInvalid();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
