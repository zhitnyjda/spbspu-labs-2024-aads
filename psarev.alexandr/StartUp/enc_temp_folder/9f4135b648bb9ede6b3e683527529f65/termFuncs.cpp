#include "termFuncs.hpp"
#include <limits>

bool psarev::checkOperand(std::string symbol)
{
  for (char c : symbol)
  {
    if (std::isdigit(c))
    {
      return true;
    }
  }
  return false;
}

bool psarev::checkOperator(std::string c)
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

void psarev::makeQueue(std::string strTerm, Queue< std::string >& queue)
{
  std::string symb = "";
  size_t i = 0;
  while (i < strTerm.length())
  {
    if (strTerm[i] == ' ')
    {
      i++;
      queue.push(symb);
      symb = "";
    }
    else if (i == (strTerm.length() - 1))
    {
      symb += strTerm[i];
      i++;
      queue.push(symb);
    }
    else
    {
      symb += strTerm[i];
      i++;
    }
  }
}

void psarev::postfixation(Queue< std::string >& term, Queue< std::string >& result)
{
  Stack< std::string > stack;

  while (!term.isEmpty())
  {
    std::string elem = term.getFront();
    term.pop();
    if (checkOperand(elem))
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

long long psarev::makeOperation(long long firValue, long long secValue, std::string operation)
{
  long long res = 0;
  if (operation == "+")
  {
    res = firValue + secValue;
  }
  else if (operation == "-")
  {
    res = firValue - secValue;
  }
  else if (operation == "/")
  {
    res = firValue / secValue;
  }
  else if (operation == "*")
  {
    res = firValue * secValue;
  }
  else if (operation == "%")
  {
    res = firValue < 0 ? (firValue % secValue + secValue) : firValue % secValue;
  }
  else
  {
    res = 0;
  }

  return res;
}

long long psarev::calculateTerm(Queue< std::string >& term)
{
  Stack< long long > stack;
  std::string elem;
  long long firVal;
  long long secVal;
  while (!term.isEmpty())
  {
    elem = term.getFront();
    term.pop();
    if (checkOperand(elem))
    {
      stack.push(std::stoll(elem));
    }
    else if (checkOperator(elem))
    {
      secVal = stack.getTop();
      stack.pop();
      firVal = stack.getTop();
      stack.pop();
      stack.push(makeOperation(firVal, secVal, elem));
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

void psarev::makeResults(Queue< std::string >& terms, Stack< long long >& results)
{
  std::string strTerm;
  long long res = 0;

  Queue< std::string > infixTrem;
  Queue< std::string > postfixTerm;

  while (!terms.isEmpty())
  {
    strTerm = terms.getFront();
    terms.pop();
    makeQueue(strTerm, infixTrem);
    postfixation(infixTrem, postfixTerm);
    res = calculateTerm(postfixTerm);
    results.push(res);
  }
}
