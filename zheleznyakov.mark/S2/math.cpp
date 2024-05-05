#include "math.hpp"

void zheleznyakov::processProblems(Queue< std::string > & problems)
{
  while (!problems.empty())
  {
    Queue< std::string > infix;
    Queue< std::string > postfix;
    tokenize(problems.front(), infix);
    infixToPostfix(infix, postfix);
    std::cout << calculatePostfix(postfix) << '\n';
    problems.pop();
  }
}

long long zheleznyakov::calculatePostfix(Queue< std::string > & expression)
{
  Stack < long long > stack;
  while (!expression.empty())
  {
    std::string token = expression.front();
    expression.pop();
    if (isdigit(token[0]))
    {
      stack.push(std::stoi(token));
    }
    else
    {
      int operand2 = stack.top();
      stack.pop();
      int operand1 = stack.top();
      stack.pop();
      if (token[0] == '+')
      {
        stack.push(operand1 + operand2);
      }
      else if (token[0] == '-')
      {
        stack.push(operand1 - operand2);
      }
      else if (token[0] == '*')
      {
        stack.push(operand1 * operand2);
      }
      else if (token[0] == '/')
      {
        stack.push(operand1 / operand2);
      }
      else if (token[0] == '%')
      {
        stack.push(operand1 % operand2);
      }
    }
  }

  return stack.top();
};
