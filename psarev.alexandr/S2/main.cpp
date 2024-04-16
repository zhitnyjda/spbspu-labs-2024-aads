#include <iostream>
#include "queue.hpp"
#include "stack.hpp"
#include "termFuncs.hpp"

int main(int argc, char* argv[])
{
  psarev::Stack< std::string > symbolSeq;
  if (argc == 1)
  {
    psarev::inputTerm(symbolSeq, std::cin);
  }
  else if (argc == 2)
  {
    std::ifstream readTerm(argv[1]);
    inputTerm(symbolSeq, readTerm);
  }
  else
  {
    std::cerr << "Error: Not enough arguments!";
    return 1;
  }
  return 0;
}