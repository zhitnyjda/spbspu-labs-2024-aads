#include "inputFunctions.hpp"

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
