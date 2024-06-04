#include <iostream>
#include <list>
#include <deque>
#include "output.hpp"
#include "sorts.hpp"
#include "random.hpp"

int main(int argc, char * argv[])
{
  using namespace zheleznyakov;

  if (argc != 4)
  {
    errors::wrongArgsCount(std::cerr);
    return 2;
  }

  std::string order = argv[1];
  if (order != "ascending" && order != "descending")
  {
    errors::wrongSortOrder(std::cerr);
    return 1;
  }

  std::string dataType = argv[2];
  if (dataType != "ints" && dataType != "floats")
  {
    errors::wrongDataType(std::cerr);
    return 1;
  }

  int count = std::atoi(argv[3]);
  if (count <= 0)
  {
    errors::wrongSize(std::cerr);
    return 1;
  }

  std::cout << order << ' ' << dataType << ' ' << count << '\n';

  return 0;
}
