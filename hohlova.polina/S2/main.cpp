#include <iostream>
#include "ExpressionCalc.h"
#include <fstream>


int main(int argc, char** argv)
{
  hohlova::ExpressionCalc calculator;
  hohlova::Stack<long long> results;
  if(argc == 1)
  {
    calculator.readExpression(std::cin);
  }
  else if(argc == 2)
  {
    std::ifstream stream(argv[1]);
    calculator.readExpression(stream);
  }
  else
  {
    std::cerr << "Invalid number of command line arguments";
  }
  try
  {
    calculator.CalculateExpressions(results);
  }
  catch (const std::runtime_error& err)
  {
    std::cout << err.what();
    return 1;
  }

  while(!results.empty())
  {
    std::cout << results.top() << ' ';
    results.pop();
  }
  return 0;
  std::cout << "\n";
}
