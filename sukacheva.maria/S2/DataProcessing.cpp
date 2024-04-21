#include "DataProcessing.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Stack.hpp"
#include "Queue.hpp"

sukacheva::Queue< std::string > sukacheva::inputStatement(std::istream& input)
{
  input >> std::noskipws;
  std::string line = "";
  std::string num = "";
  Queue< std::string > statement;
  std::getline(input, line);
  for (size_t i = 0; i < line.length(); i++)
  {
    if (line[i] == ' ')
    {
      if (!num.empty())
      {
        statement.push(num);
      }
      num = "";
    }
    else
    {
      num += line[i];
    }
  }
  if (!num.empty())
  {
    statement.push(num);
  }
  return statement;
}

bool sukacheva::isNumber(std::string example)
{
  return !example.empty() && (example.find_first_not_of("0123456789") == example.npos);
}

bool sukacheva::isBinaryOperations(std::string example)
{
  return !example.empty() && (example.find_first_not_of("+-*/%") == example.npos);
}

bool sukacheva::priorityOfOperation(std::string operation1, std::string operation2)
{
  int priorityIndex1 = 1;
  int priorityIndex2 = 1;
  if (operation1.find_first_not_of("*/%") == operation1.npos)
  {
    priorityIndex1 = 2;
  }
  if (operation2.find_first_not_of("*/%") == operation2.npos)
  {
    priorityIndex2 = 2;
  }
  else if (operation2 == "(")
  {
    return 0;
  }
  return priorityIndex1 >= priorityIndex2;
}

sukacheva::Queue<std::string> sukacheva::makePostfix(Queue< std::string >& infix)
{
  sukacheva::Stack< std::string > temp;
  sukacheva::Queue< std::string > postfix;
  while (!infix.empty()) {
    if (infix.front() == "(")
    {
      temp.push(infix.front());
      infix.pop();
    }
    else if (infix.front() == ")")
    {
      if (temp.empty())
      {
        throw std::logic_error("incorrect statement notation :)");
      }
      else
      {
        while (temp.top() != "(")
        {
          postfix.push(temp.top());
          temp.pop();
        }
        infix.pop();
        temp.pop();
      }
    }
    else if (isNumber(infix.front()))
    {
      postfix.push(infix.front());
      infix.pop();
    }
    else if (isBinaryOperations(infix.front()))
    {
      if (!temp.empty())
      {
        while (!temp.empty() && priorityOfOperation(infix.front(), temp.top()))
        {
          postfix.push(temp.top());
          temp.pop();
        }
      }
      temp.push(infix.front());
      infix.pop();
    }
    else
    {
      throw std::logic_error("invalid argument >:( ");
    }
  }
  while (!temp.empty())
  {
    if (temp.top() != "(")
    {
      postfix.push(temp.top());
      temp.pop();
    }
    else
    {
      throw std::logic_error("incorrect statement notation :)");
    }
  }
  return postfix;
}

long long sukacheva::calculate(Queue< std::string >& postfix)
{
  Stack< long long > stack;
  const long long maxValue = std::numeric_limits< long long >::max();
  const long long minValue = std::numeric_limits< long long >::min();
  while (!postfix.empty())
  {
    if (isNumber(postfix.front()))
    {
      stack.push(std::stoull(postfix.front()));
      postfix.pop();
    }
    else if (isBinaryOperations(postfix.front()))
    {
      if (stack.getSize() >= 2) {
        long long operand2 = stack.top();
        stack.pop();
        long long operand1 = stack.top();
        stack.pop();

        if (postfix.front() == "+")
        {
          if (operand1 > maxValue - operand2)
          {
            throw std::logic_error("overflow observed !!!");
          }
          else
          {
            stack.push(operand1 + operand2);
          }
        }
        else if (postfix.front() == "-")
        {
          if (operand1 < minValue + operand2)
          {
            throw std::logic_error("overflow observed !!!");
          }
          else
          {
            stack.push(operand1 - operand2);
          }
        }
        else if (postfix.front() == "*")
        {
          if ((operand1 > maxValue / operand2) || (operand1 <= minValue / operand2))
          {
            throw std::logic_error("overflow observed !!!");
          }
          else
          {
            stack.push(operand1 * operand2);
          }
        }
        else if (postfix.front() == "/")
        {
          if ((operand1 / operand2 > maxValue) || (operand1 / operand2 <= minValue))
          {
            throw std::logic_error("overflow observed !!!");
          }
          else if (operand2 != 0)
          {
            stack.push(operand1 / operand2);
          }
          else
          {
            throw std::logic_error("division by zero !!!");
          }
        }
        else if (postfix.front() == "%")
        {
          stack.push((operand1 % operand2) < 0 ? (operand1 % operand2) + operand2 : (operand1 % operand2));
        }
        postfix.pop();
      }
      else
      {
        throw std::logic_error("incorrect statement notation :)");
      }
    }
  }
  return stack.top();
}
