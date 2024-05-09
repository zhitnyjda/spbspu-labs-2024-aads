#include "termFuncs.hpp"
#include <limits>

void psarev::readTerms(std::istream& input, Queue< std::string >& terms)
{
  std::string inputLine;
  while (!input.eof())
  {
    std::getline(input, inputLine);
    if (!inputLine.empty())
    {
      terms.push(inputLine);
    }
  }
}

void psarev::strToQueue(std::string expression, Queue< std::string >& result)
{
  std::string symbol = "";
  size_t i = 0;
  while (i < expression.length())
  {
    if (expression[i] == ' ')
    {
      i++;
      result.push(symbol);
      symbol = "";
    }
    else if (i == (expression.length() - 1))
    {
      symbol += expression[i];
      i++;
      result.push(symbol);
    }
    else
    {
      symbol += expression[i];
      i++;
    }
  }
}

bool psarev::isOperand(std::string symbol)
{
  for (char c : symbol)
  {
    if (!std::isdigit(c))
    {
      return false;
    }
  }
  return true;
}

bool psarev::isOperator(std::string c)
{
  if (c == "/" || c == "*" || c == "+" || c == "-" || c == "%")
  {
    return true;
  }
  return false;
}

int psarev::priori(std::string c)
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

void psarev::postfixation(Queue< std::string >& term, Queue< std::string >& result)
{
  Stack< std::string > stack;

  while (!term.isEmpty())
  {
    std::string elem = term.getFront();
    term.pop();
    if (isOperand(elem))
    {
      result.push(elem);
    }
    else if (elem == "(")
    {
      stack.push("(");
    }
    else if (elem == ")")
    {
      while (stack.getTop() != "(")
      {
        result.push(stack.getTop());
        stack.pop();
      }
      stack.pop();
    }
    else
    {
      while ((!stack.isEmpty() && priori(elem) < priori(stack.getTop())) ||
        (!stack.isEmpty() && priori(elem) == priori(stack.getTop())))
      {
        result.push(stack.getTop());
        stack.pop();
      }
      stack.push(elem);
    }
  }
  while (!stack.isEmpty())
  {
    result.push(stack.getTop());
    stack.pop();
  }
}

long long psarev::makeOper(long long firVal, long long secVal, std::string operation)
{
  long long res = 0;
  if (operation == "+")
  {
    res = firVal + secVal;
  }
  else if (operation == "-")
  {
    res = firVal - secVal;
  }
  else if (operation == "/")
  {
    res = firVal / secVal;
  }
  else if (operation == "*")
  {
    res = firVal * secVal;
  }
  else if (operation == "%")
  {
    res = firVal < 0 ? (firVal % secVal + secVal) : firVal % secVal;
  }
  else
  {
    res = 0;
  }

  return res;
}

long long psarev::calculateExpr(Queue< std::string >& term)
{
  Stack< long long > stack;
  std::string elem;
  long long firVal;
  long long secVal;
  while (!term.isEmpty())
  {
    elem = term.getFront();
    term.pop();
    if (isOperand(elem))
    {
      stack.push(std::stoll(elem));
    }
    else if (isOperator(elem))
    {
      secVal = stack.getTop();
      stack.pop();
      firVal = stack.getTop();
      stack.pop();
      stack.push(makeOper(firVal, secVal, elem));
    }
    else
    {
      throw std::logic_error("incorrect expression");
    }
  }
  unsigned long long result = stack.getTop();
  stack.pop();
  return result;
}

void psarev::formResultStack(Queue< std::string >& terms, Stack< long long >& resultStack)
{
  std::string curStrExpr;
  Queue< std::string > curInfixExpr;
  Queue< std::string > curPostfixExpr;
  long long curAnswer = 0;
  while (!terms.isEmpty())
  {
    curStrExpr = terms.getFront();
    terms.pop();
    strToQueue(curStrExpr, curInfixExpr);
    postfixation(curInfixExpr, curPostfixExpr);
    curAnswer = calculateExpr(curPostfixExpr);
    resultStack.push(curAnswer);
  }
}
