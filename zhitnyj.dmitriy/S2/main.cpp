#include <iostream>
#include <fstream>
#include <string>
#include "Queue.hpp"
#include "Stack.hpp"
#include "ExpressionItem.hpp"
#include "ExpressionEvaluator.hpp"
#include "Operand.hpp"
#include "Operator.hpp"

int main(int argc, char* argv[])
{
  Queue< std::shared_ptr< ExpressionItem>> expressionQueue;
  Stack< long long > results;

  try
  {
    std::string line;
    if (argc > 1)
    {
      std::ifstream file(argv[1]);
      if (!file)
      {
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
      }
      while (std::getline(file, line))
      {
        if (!line.empty())
        {
          ExpressionEvaluator::parseExpression(expressionQueue, line);
          Queue< std::shared_ptr< ExpressionItem>> postfixQueue = ExpressionEvaluator::toPostfix(expressionQueue);
          results.push_back(ExpressionEvaluator::evaluateExpression(postfixQueue));
          expressionQueue.clear();
        }
      }
    }
    else
    {
      while (std::getline(std::cin, line))
      {
        if (!line.empty())
        {
          ExpressionEvaluator::parseExpression(expressionQueue, line);
          Queue< std::shared_ptr< ExpressionItem>> postfixQueue = ExpressionEvaluator::toPostfix(expressionQueue);
          results.push_back(ExpressionEvaluator::evaluateExpression(postfixQueue));
          expressionQueue.clear();
        }
      }
    }

    if (results.empty())
    {
      std::cout << "\n";
    }
    while (!results.empty())
    {
      std::cout << results.top() << " ";
      results.pop();
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
