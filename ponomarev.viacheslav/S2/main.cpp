#include <iostream>
#include <fstream>
#include "inputFunctions.hpp"
#include "queue.hpp"
#include "stack.hpp"

int main(int argc, char ** argv)
{
  ponomarev::Queue< std::string > expressions;
  ponomarev::Stack< long long > results;

  if (argc == 1)
  {
    ponomarev::inputExpressions(std::cin, expressions);
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
    ponomarev::inputExpressions(input, expressions);
  }
  else
  {
    std::cerr << "Error: wrong input";
    return 1;
  }

  return 0;
}
