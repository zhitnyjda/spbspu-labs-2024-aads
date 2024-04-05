#include "processingFunctions.hpp"
#include <limits>
#include "inputFunctions.hpp"
#include "queue.hpp"

bool redko::isNumeric(const std::string & str)
{
  return str.find_first_not_of("0123456789") == std::string::npos && str.size() != 0;
}

void redko::processExpressions(std::istream & input, Stack< long long > & res)
{
  std::string expression = "";
  std::string value = "";
  while (!input.eof())
  {
    Queue< std::string > postfix{};
    Stack< std::string > stack{};
    std::getline(input, expression);
    while (!expression.empty())
    {
      value = cutName(expression);
      if (isNumeric(value))
      {
        postfix.push(value);
      }
      else
      {
        if (value == "(")
        {
          stack.push(value);
        }
        else if (value == "+" || value == "-")
        {
          while (!stack.empty() && (stack.top() == "+" || stack.top() == "-" || stack.top() == "%" || stack.top() == "*" || stack.top() == "/"))
          {
            postfix.push(stack.top());
            stack.pop();
          }
          stack.push(value);
        }
        else if (value == "%" || value == "*" || value == "/")
        {
          while (!stack.empty() && (stack.top() == "%" || stack.top() == "*" || stack.top() == "/"))
          {
            postfix.push(stack.top());
            stack.pop();
          }
          stack.push(value);
        }
        else if (value == ")")
        {
          while (!stack.empty() && stack.top() != "(")
          {
            postfix.push(stack.top());
            stack.pop();
          }
          stack.pop();
        }
        else
        {
          throw std::invalid_argument("Error: wrong expression");
        }
      }
    }
    while (!stack.empty())
    {
      postfix.push(stack.top());
      stack.pop();
    }
    if (!postfix.empty())
    {
      Stack< long long > calc{};
      long long rOperand = 0;
      long long lOperand = 0;

      while (!postfix.empty())
      {
        if (isNumeric(postfix.front()))
        {
          calc.push(stoll(postfix.front()));
        }
        else
        {
          rOperand = calc.top();
          calc.pop();
          lOperand = calc.top();
          calc.pop();
          if (postfix.front() == "+")
          {
            if (rOperand > 0 && lOperand > 0 && (rOperand > std::numeric_limits< long long >::max() - lOperand))
            {
              throw std::overflow_error("Error: unable to calculate due to overflow");
            }
            else if (rOperand < 0 && lOperand < 0 && (rOperand < std::numeric_limits< long long >::min() - lOperand))
            {
              throw std::underflow_error("Error: unable to calculate due to underflow");
            }
            calc.push(lOperand + rOperand);
          }
          else if (postfix.front() == "-")
          {
            if (lOperand > 0 && rOperand < 0 && (lOperand > std::numeric_limits< long long >::max() + rOperand))
            {
              throw std::overflow_error("Error: unable to calculate due to overflow");
            }
            else if (lOperand < 0 && rOperand > 0 && (lOperand < std::numeric_limits< long long >::min() + rOperand))
            {
              throw std::underflow_error("Error: unable to calculate due to underflow");
            }
            calc.push(lOperand - rOperand);
          }
          else if (postfix.front() == "*")
          {
            if (((lOperand > 0 && rOperand > 0) || (lOperand < 0 && rOperand < 0)) && (rOperand > std::numeric_limits< long long >::max() / lOperand))
            {
              throw std::overflow_error("Error: unable to calculate due to overflow");
            }
            else if (((lOperand > 0 && rOperand < 0) || (lOperand < 0 && rOperand > 0)) && (rOperand < std::numeric_limits< long long >::min() / lOperand))
            {
              throw std::underflow_error("Error: unable to calculate due to underflow");
            }
            calc.push(lOperand * rOperand);
          }
          else if (postfix.front() == "/")
          {
            if (rOperand == 0)
            {
              throw std::logic_error("Error: division by 0");
            }
            calc.push(lOperand / rOperand);
          }
          else
          {
            if (rOperand == 0)
            {
              throw std::logic_error("Error: mod by 0");
            }
            calc.push(lOperand % rOperand + rOperand);
          }
        }
        postfix.pop();
      }
      res.push(calc.top());
    }
  }
}
