#include "computationalFunctions.hpp"
#include "stack.hpp"
#include "cutFunctions.hpp"

void ponomarev::getPostfix(std::string expression, Postfix & queue)
{
  Stack< ExpressionElement > stack;

  while (!(expression.empty()))
  {
    ExpressionElement elem = getElem(expression);
    if (elem.getType() == "Bracket")
    {
      if (elem.bracket.isOpenBracket())
      {
        stack.push(elem);
      }
      else
      {
        while (!(isOpenBracketUp(stack)))
        {
          queue.postfix.push(stack.getUp());
          stack.pop();
        }
        stack.pop();
      }
    }
    else if (elem.getType() == "Operand")
    {
      queue.postfix.push(elem);
    }
    else if (elem.getType() == "operation")
    {
      while (!shouldPushOpToStack(stack, elem))
      {
        queue.postfix.push(stack.getUp());
        stack.pop();
      }
      stack.push(elem);
    }
  }
  while (!stack.empty())
  {
    queue.postfix.push(stack.getUp());
    stack.pop();
  }
}

bool ponomarev::isNum(const std::string & elem)
{
  return elem.find_first_not_of("0123456789") == std::string::npos && elem.size() != 0;
}

ponomarev::ExpressionElement ponomarev::getElem(std::string & expression)
{
  ponomarev::ExpressionElement elem;
  std::string arg = getName(expression);
  if (isNum(arg))
  {
    elem.putOperand(std::stoi(arg));
  }
  else if (arg == "+" || arg == "-" || arg == "%" || arg == "*" || arg == "/")
  {
    elem.putOperation(arg[0]);
  }
  else if (arg == "(" || arg == ")")
  {
    elem.putBracket(arg[0]);
  }
  else
  {
    throw std::invalid_argument("Error: wrong expression");
  }
  return elem;
}

bool ponomarev::isOpenBracketUp(const Stack< ExpressionElement > & stack)
{
  if (stack.empty())
  {
    return false;
  }

  bool isBracketUp = stack.getUp().getType() != "Bracket";
  if (isBracketUp)
  {
    return false;
  }

  bool bracketIsOpening = stack.getUp().getBracket().bracket_ != '(';
  if (bracketIsOpening)
  {
    return false;
  }

  return true;
}

bool ponomarev::shouldPushOpToStack(const Stack< ExpressionElement > & stack, const ExpressionElement & elem)
{
  if (stack.empty())
  {
    return true;
  }

  bool isOperationUp = stack.getUp().getType() != "operation";
  if (isOperationUp)
  {
    return true;
  }

  if (elem.getBracket().priority_ < stack.getUp().getBracket().priority_)
  {
    return true;
  }

  return false;
}
