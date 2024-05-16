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

  using base_t = psarev::avlTree< int, std::string >;
  avlTree< std::string, base_t > dataSets;
  
  psarev::fillTree(input, dataSets);

  psarev::avlTree< std::string, std::function< void(psarev::avlTree< std::string, base_t >&, std::string&) > > taskCmds;
}
