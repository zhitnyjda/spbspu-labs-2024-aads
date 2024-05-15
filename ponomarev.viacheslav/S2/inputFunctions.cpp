#include "inputFunctions.hpp"
#include <istream>

void ponomarev::inputExpressions(std::istream & input, Queue< std::string > & expressions)
{
  std::string expression = "";
  while (!input.eof())
  {
    std::getline(input, expression);
    if (!expression.empty())
    {
      expressions.push(expression);
    }
  }
}

void ponomarev::getResults(Queue< std::string > & expressions, Stack< int > & res)
{
  std::string expression;
  int resOfExpression = 0;
  Queue< std::string > postfix;

  while (!expressions.empty())
  {
    expression = expressions.getElem();
    expressions.pop();
    res.push(resOfExpression);
  }
}
