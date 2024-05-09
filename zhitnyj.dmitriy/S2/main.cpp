#include <iostream>
#include <fstream>
#include <string>
#include "Queue.hpp"
#include "Stack.hpp"
#include "ExpressionItem.hpp"
#include "ExpressionEvaluator.hpp"

int main(int argc, char* argv[])
{
  Queue< std::shared_ptr< ExpressionItem > > expressionQueue;
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
          results.push(ExpressionEvaluator::evaluateExpression(postfixQueue));
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
          results.push(ExpressionEvaluator::evaluateExpression(postfixQueue));
          expressionQueue.clear();
        }
      }
    }

    while (!results.empty())
    {
      std::cout << results.top() << (results.size() == 1 ? "" : " ");
      results.pop();
    }
    std::cout << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
