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
  psarev::avlTree< std::string, base_t > dataSets;
  
  psarev::fillTree(input, dataSets);

  psarev::avlTree< std::string, std::function< void(psarev::avlTree< std::string, base_t >&, std::string&) > > taskCmds;
  taskCmds.insert("print", print);
  taskCmds.insert("complement", complement);
  taskCmds.insert("intersect", intersect);
  taskCmds.insert("union", unite);

  std::string taskCmd = "";
  while (std::cin >> taskCmd)
  {
    try
    {
      taskCmds.at(taskCmd)(std::cin, std::cout, dataSets);
    }
    catch (const std::out_of_range& e)
    {
      psarev::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
