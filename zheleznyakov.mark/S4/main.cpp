#include <iostream>
#include <fstream>
#include "tree.hpp"

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

  return 0;
}
