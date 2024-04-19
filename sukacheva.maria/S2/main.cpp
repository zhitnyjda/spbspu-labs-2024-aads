#include <fstream>
#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
#include <iosfwd>
#include <string>
#include "DataProcessing.hpp"

int main(int argc, char* argv[])
{
  using namespace sukacheva;
  if (argc == 1)
  {
    try
    {
      long long result = 0;
      while (std::cin)
      {
        Queue< std::string > inf = inputStatement(std::cin);
        Queue< std::string > test = makePostfix(inf);
        result = calculate(test);
        std::cout << result << "\n";
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
  }
  else
  {
    std::cerr << "wrong number of args";
  }
  return 0;
}
