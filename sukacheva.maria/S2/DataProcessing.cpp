#include "DataProcessing.hpp"
#include <iostream>
#include <fstream>
#include <string>
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
      num = {};
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
      while (temp.top() != "(")
      {
        postfix.push(temp.top());
        temp.pop();
      }
      infix.pop();
      temp.pop();
    }
    else if (isNumber(infix.front()))
    {
      postfix.push(infix.front());
      infix.pop();
    }
    else if (isBinaryOperations(infix.front()))
    {
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
    postfix.push(temp.top());
    temp.pop();
  }
  return postfix;
}

long long sukacheva::calculate(Queue< std::string >& postfix)
{
  Stack< long long > stack;
  while (!postfix.empty()) {
    if (isNumber(postfix.front())) {
      stack.push(std::stoull(postfix.front()));
      postfix.pop();
    }
    else if (isBinaryOperations(postfix.front()))
    {
      long long operand2 = stack.top();
      stack.pop();
      long long operand1 = stack.top();
      stack.pop();

      if (postfix.front() == "+")
      {
        stack.push(operand1 + operand2);
      }
      else if (postfix.front() == "-")
      {
        stack.push(operand1 - operand2);
      }
      else if (postfix.front() == "*")
      {
        stack.push(operand1 * operand2);
      }
      else if (postfix.front() == "/")
      {
        stack.push(operand1 / operand2);
      }
      else if (postfix.front() == "%")
      {
        stack.push(operand1 % operand2);
      }
      postfix.pop();
    }
  }
  if (!stack.empty()) {
    return stack.top();
  }
}
