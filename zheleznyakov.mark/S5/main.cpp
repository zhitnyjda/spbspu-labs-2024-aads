#include <iostream>
#include <fstream>
#include <tree.hpp>
#include "input.hpp"

int main(int argc, char * argv[])
{
  using namespace zheleznyakov;

  if (argc != 3)
  {
    std::cerr << "Wrong arguments count\n";
    return 2;
  }

  std::ifstream in(argv[2]);
  if (!in)
  {
    std::cerr << "Unable to read file\n";
    return 2;
  }

  data_t data;
  std::string line;
  std::getline(in, line);
  readData(line, data);

  

  std::string command = argv[1];

  return 0;
}
