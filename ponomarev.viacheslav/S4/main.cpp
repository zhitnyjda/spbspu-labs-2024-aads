#include <fstream>
#include <iostream>
#include <limits>
#include "IOFunctions.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "error: wrong parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "error: can't open the file\n";
    return 1;
  }

  using data_t = ponomarev::BSTree< int, std::string, int >;
  using tree_t = ponomarev::BSTree< std::string, data_t, int >;
  tree_t data;
  ponomarev::inputFromFile(input, data);
  BSTree< std::string, tree_t, int > commands;
  {
  }

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, data);
    }
    catch (const std::out_of_range & e)
    {
      ponomarev::printInvalidCommandMessage(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
