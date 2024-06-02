#include <fstream>
#include <iostream>
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
  ponomarev::BSTree< std::string, data_t, int > data;
  ponomarev::inputFromFile(input, data);
}
