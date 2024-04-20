#include <iostream>
#include <fstream>
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
      Stack< long long > resultsOfCalculate;
      while (!std::cin.eof())
      {
        Queue< std::string > inf = inputStatement(std::cin);
        Queue< std::string > test = makePostfix(inf);
        resultsOfCalculate.(calculate(test));
      }
      resultsOfCalculate.pop();
      while (!resultsOfCalculate.empty())
      {
        std::cout << resultsOfCalculate.top();
        resultsOfCalculate.pop();
        if (!resultsOfCalculate.empty())
        {
          std::cout << " ";
        }
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
