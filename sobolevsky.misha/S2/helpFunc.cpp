#include "helpFunc.hpp"
#include <sstream>

void sobolevsky::fillStack(std::istream & in, Stack< std::string > & container)
{
  std::string input;
  while (getline(in, input))
  {
    container.push(input);
  }
}

bool sobolevsky::isDigit(std::string c)
{
  for(size_t i = 0; i < c.length(); i++)
  {
    if (!('0' <= c[i] && c[i] <= '9'))
    {
      return false;
    }
  }
  return true;
}

int sobolevsky::algebrChars(std::string c)
{
  if (c == "/" || c == "*" || c == "%")
  {
    return 2;
  }
  else if (c == "+" || c == "-")
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

size_t sobolevsky::counter(std::string ch, size_t first, size_t second)
{
  if(ch == "+")
  {
    return first + second;
  }
  else if(ch == "-")
  {
    return first - second;
  }
  else if(ch == "*")
  {
    return first * second;
  }
  else if(ch == "/")
  {
    return first / second;
  }
  else
  {
    return first % second;
  }
}

std::string* sobolevsky::fromInfixToPostfix(std::string infixExpression, size_t &i)
{
  std::string *postfixExpression = new std::string[infixExpression.length()]();
  std::string str;
  sobolevsky::Stack< std::string > stack;
  std::stringstream ss(infixExpression);
  while (getline(ss, str, ' '))
  {
    if (isDigit(str))
    {
      postfixExpression[i] = str;
      i++;
    }
    else if (str == "(")
    {
      stack.push("(");
    }
    else if (str == ")")
    {
      while(stack.top() != "(")
      {
        postfixExpression[i] = stack.top();
        i++;
        stack.pop();
      }
      stack.pop();
    }
    else
    {
      while (!stack.empty() && algebrChars(str) <= algebrChars(stack.top()))
      {
        postfixExpression[i] = stack.top();
        i++;
        stack.pop();
      }
      stack.push(str);
    }
  }

  while (!stack.empty())
  {
    postfixExpression[i] = stack.top();
    i++;
    stack.pop();
  }

  return postfixExpression;
}

size_t sobolevsky::countPostfix(std::string *postfix, size_t length)
{
  sobolevsky::Stack< size_t > stack;

  for(size_t j = 0; j < length; j++)
  {
    if (isDigit(postfix[j]))
    {
      stack.push(std::stoll(postfix[j]));
    }
    else
    {
      size_t second = stack.top();
      stack.pop();
      size_t first = stack.top();
      stack.pop();
      size_t result = counter(postfix[j], first, second);
      stack.push(result);
    }
  }

  delete[] postfix;

  return stack.top();
}
