#include <iostream>
#include <limits>
#include <fstream>
#include <map> // TODO: delete
#include "tree.hpp"
#include "IOProcessing.hpp"

// int main()
int main(int argc, char* argv[])
{
  using namespace miheev;

  if (argc != 2)
  {
    std::cerr << "Wrong amount of launch parameters\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Error while opening file\n";
  }

  Tree< std::string, Data > datasets;
  while (!file.eof())
  {
    inputDatasets(file, datasets);
    if (file.fail() && !file.eof())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
