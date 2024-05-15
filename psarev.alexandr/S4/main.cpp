#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "AVLtree.hpp"
#include "execCommands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: Can't open a file!\n";
    return 2;
  }

  using namespace psarev;
  avlTree< std::string, avlTree< int, std::string > > dataSets;
  avlTree< std::string, std::function< void(avlTree< std::string, avlTree< int, std::string > >&, std::string&) > > taskCmds;

  std::string cmd;
  while (!std::cin.eof())
  {
    try
    {
      taskCmds[command](dataSets);
    }
    catch (const std::logic_error&)
    {
      psarev::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}