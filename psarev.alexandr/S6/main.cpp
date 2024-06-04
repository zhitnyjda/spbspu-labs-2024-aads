#include <map>
#include <iostream>
#include <functional>
#include "utilFuncs.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  int size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "Error: Size must be positive!\n";
    return 2;
  }

  std::map< std::string, std::map < std::string, std::function< void(std::ostream&, int) > > > sortFuncs;
  {
    using namespace std::placeholders;
    sortFuncs["ints"]["ascending"] = std::bind(psarev::makeSorted< int, char >);
    sortFuncs["ints"]["descending"] = std::bind(psarev::makeSorted< int, char >);

    sortFuncs["floats"]["ascending"] = std::bind(psarev::makeSorted< double, char >);
    sortFuncs["floats"]["descending"] = std::bind(psarev::makeSorted< double, char >);
  }

}