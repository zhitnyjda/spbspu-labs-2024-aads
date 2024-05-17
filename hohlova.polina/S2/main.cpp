#include <iostream>
#include "ExpressionCalc.hpp"
#include <fstream>


int main(int argc, char** argv)
{
  hohlova::ExpressionCalc calculator;
  hohlova::Stack< long long > results;
  if (argc == 1)
  {
    calculator.readExpression(std::cin);
  }
  else if (argc == 2)
  {
    std::ifstream stream(argv[1]);
    calculator.readExpression(stream);
  }
  else
  {
    std::cerr << "Invalid number of command line arguments";
    return 1;
  }

  calculator.CalculateExpressions(results);

  while (!results.empty())
  {
    std::cout << results.top();
    results.pop();
  }
  std::cout << "\n";
  return 0;
}
