#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
#include <iosfwd>
#include <string>
#include "DataProcessing.hpp"

int main(int argc, char** argv)
{
  using namespace sukacheva;
  if (argc == 1)
  {
    try
    {
      while (std::cin)
      {
        Queue< std::string > inf = inputStatement(std::cin);
        Queue< std::string > test = makePostfix(inf);
        long long result = calculate(test);
        std::cout << result << "\n";
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  else
  {

  }
  return 0;
}