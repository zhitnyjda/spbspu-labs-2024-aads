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

sukacheva::Postfix sukacheva::makePostfix(Queue< std::string >& infix)
{
  sukacheva::Stack< ElementOfStatement* > temp;
  sukacheva::Postfix postfix;
  while (!infix.empty()) {
    ElementOfStatement val = infix.front();
    if (val.isBracket())
    {
      Bracket bracket = val.applicant;
      Bracket* bracketPointer = &bracket;
      if (bracket.ifBracketIsOpen())
      {
        temp.push(bracketPointer);
        infix.pop();
      }
      else if (bracket.ifBracketIsClose())
      {
        if (temp.empty())
        {
          throw std::logic_error("incorrect statement notation :)");
        }
        else
        {
          while (!temp.top()->isBracket())
          {
            Operation operation = temp.top()->applicant;
            postfix.operations.push(operation);
            temp.pop();
          }
          infix.pop();
          temp.pop();
        }
      }
    }
    else if (val.isNumber())
    {
      Operand operand = std::stoull(val.applicant);
      postfix.operands.push(operand);
      infix.pop();
    }
    else if (val.isBinaryOperations())
    {
      Operation operation = val.applicant;
      Operation* operationPointer = &operation;
      if (!temp.empty())
      {
        while (!temp.empty() && operation.priorityOfOperation(*temp.top()))
        {
          Operation operation = temp.top()->applicant;
          postfix.operations.push(operation);
          temp.pop();
        }
      }
      temp.push(operationPointer);
      infix.pop();
    }
    else
    {
      throw std::logic_error("invalid argument >:( ");
    }
  }
  while (!temp.empty())
  {
    if (!temp.top()->isBracket())
    {
      Operation operation = temp.top()->applicant;
      postfix.operations.push(operation);
      temp.pop();
    }
    else
    {
      throw std::logic_error("incorrect statement notation :)");
    }
  }
  return postfix;
}

long long sukacheva::calculate(Postfix& postfix)
{
  const long long maxValue = std::numeric_limits< long long >::max();
  const long long minValue = std::numeric_limits< long long >::min();
  while (!postfix.operations.empty() || !postfix.operands.empty())
  {
    if (postfix.operands.getSize() >= 2) {
      Operand operand2 = postfix.operands.top();
      postfix.operands.pop();
      Operand operand1 = postfix.operands.top();
      postfix.operands.pop();

      if (postfix.operations.top().operation == '+')
      {
        if (operand1.value > maxValue - operand2.value)
        {
          throw std::logic_error("overflow observed !!!");
        }
        else
        {
          postfix.operands.push(operand1 + operand2);
        }
      }
      else if (postfix.operations.top().operation == '-')
      {
        if (operand1.value < minValue + operand2.value)
        {
          throw std::logic_error("overflow observed !!!");
        }
        else
        {
          postfix.operands.push(operand1 - operand2);
        }
      }
      else if (postfix.operations.top().operation == '*')
      {
        if ((operand1.value > maxValue / operand2.value) || (operand1.value <= minValue / operand2.value))
        {
          throw std::logic_error("overflow observed !!!");
        }
        else
        {
          postfix.operands.push(operand1 * operand2);
        }
      }
      else if (postfix.operations.top().operation == '/')
      {
        if ((operand1.value / operand2.value > maxValue) || (operand1.value / operand2.value <= minValue))
        {
          throw std::logic_error("overflow observed !!!");
        }
        else if (operand2.value != 0)
        {
          postfix.operands.push(operand1 / operand2);
        }
        else
        {
          throw std::logic_error("division by zero !!!");
        }
      }
      else if (postfix.operations.top().operation == '%')
      {
        postfix.operands.push(operand1 % operand2);
      }
      postfix.operations.pop();
    }
    else
    {
      throw std::logic_error("incorrect statement notation :)");
    }
  }
  return postfix.operands.top().value;
}
