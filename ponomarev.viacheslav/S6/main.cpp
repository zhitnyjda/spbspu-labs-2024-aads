#include <iostream>
#include <functional>
#include <map>
#include "distributionFunctions.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "wrong number of parameters\n";
    return 2;
  }

  int size = std::atoi(argv[3]);
  if (size == 0)
  {
      std::cerr << "wrong size parameter\n";
      return 1;
  }

  std::map< std::string, std::map < std::string, std::function< void(std::ostream &, int) > > > commands;
  {
    using namespace std::placeholders;
    commands["ints"]["ascending"] = std::bind(ponomarev::makeSort< int, std::less< int > >, _1, _2, std::less< int >());
    commands["ints"]["descending"] = std::bind(ponomarev::makeSort< int, std::greater< int > >, _1, _2, std::greater< int >());
    commands["floats"]["ascending"] = std::bind(ponomarev::makeSort< double, std::less< double > >, _1, _2, std::less< double >());
    commands["floats"]["descending"] = std::bind(ponomarev::makeSort< double, std::greater< double > >, _1, _2, std::greater< double >());
  }

  try
  {
    commands.at(argv[2]).at(argv[1])(std::cout, size);
  }
  catch (const std::out_of_range &)
  {
    std::cerr << "Error: wrong parameter\n";
    return 1;
  }

  return 0;
}
