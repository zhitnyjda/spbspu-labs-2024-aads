#include <iostream>
#include <fstream>
#include <tree.hpp>
#include "input.hpp"

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

  data_t data;

  std::string line;
  std::getline(in, line);
  readLine(line, data);

  for (auto it = data.cbegin(); it != data.cend(); ++it)
  {
    std::cout << it->first << ' ' << it->second << '\n';
  }

  return 0;
}
