#include <iostream>
#include <tree.hpp>
#include <string>
#include "IOProcessing.hpp"

int main(int argc, char* argv[])
{
  using namespace miheev;

  srand(42);

  if (argc != 4)
  {
    printError(std::cerr, "wrong amount of parameters");
    return 1;
  }

  size_t size = std::stoull(argv[3]);
  if (size < 1)
  {
    printError(std::cerr, "inapropriate value of parameter [size]");
    return 2;
  }

  using SortFunctions = Tree< std::string, std::function< void(std::ostream&, size_t) > >;
  Tree <std::string, SortFunctions > typedFuncs;
  {
    using namespace std::placeholders;
    typedFuncs["floats"]["ascending"] = std::bind(miheev::testSorts< double, std::less< double> >, _1, _2, std::less< double >{});
    typedFuncs["floats"]["descending"] = std::bind(miheev::testSorts< double, std::greater< double> >, _1, _2, std::greater< double >{});
    typedFuncs["ints"]["ascending"] = std::bind(miheev::testSorts< int, std::less< int> >, _1, _2, std::less< int >{});
    typedFuncs["ints"]["descending"] = std::bind(miheev::testSorts< int, std::greater< int> >, _1, _2, std::greater< int >{});
  }
  
  return 0;
}
