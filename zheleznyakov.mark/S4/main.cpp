#include <iostream>
#include <fstream>
#include <limits>
#include "tree.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace zheleznyakov;
  
  if (argc != 2)
  {
    std::cerr << "Wrong arguments count\n";
    return 2;
  }

  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Unable to read file\n";
    return 2;
  }

  dicts_t dicts;
  dicts.insert("dict1", {});

  Tree< std::string, std::function< void(std::istream &, std::ostream &, dicts_t &) > > cmds;
  cmds["print"] = commands::print;

  std::string curremtCmd = "";
  while (std::cin >> curremtCmd)
  {
    try
    {
      cmds.at(curremtCmd)(std::cin, std::cout, dicts);
    }
    catch (std::out_of_range &)
    {
      outInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
