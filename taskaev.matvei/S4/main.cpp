#include <string>
#include <fstream>
#include <limits>
#include "BSTree.hpp"
#include "functions.hpp"
using namespace taskaev;

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: argument of file failed!\n";
    return 1;
  }
  BSTree< std::string, BSTree< size_t, std::string > > tres;
  std::ifstream inputs(argv[1]);
  if (!inputs)
  {
    std::cerr << "Error: not open file!\n";
    return 1;
  }
  createTree(inputs, tres);
  return 0;
}
