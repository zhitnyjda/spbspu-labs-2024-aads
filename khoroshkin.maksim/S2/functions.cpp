#include "functions.hpp"
#include "typization.hpp"

void khoroshkin::inputInfix(std::istream & in, Stack< std::string > & expressions)
{
  std::string expression;
  while (getline(in, expression))
  {
    expressions.push(expression);
  }
}

bool khoroshkin::isdigit(const std::string & str)
{
  for (char c : str)
  {
    if (!std::isdigit(c))
    {
      return false;
    }
  }
  return !str.empty();
}

long long khoroshkin::calc(std::string str)
{
  str = "( " + str + " )";
  Postfix expression;
  size_t pos = 0;
  std::string token;
  do
  {
    token = getToken(str, pos);
    if (khoroshkin::isdigit(token))
    {
      expression.operands.push(std::stoi(token));
    }
    else if (token.size() == 1)
    {
      if (token[0] == ')')
      {
        while (!expression.operations.empty() && expression.operations.top() != '(')
        {
          expression.popOperation();
        }
        expression.operations.pop();
      }
      else
      {
        while (expression.canPop(token[0]))
        {
          expression.popOperation();
        }
        expression.operations.push((token[0]));
      }
    }
  }
  while (!token.empty());

  if (expression.operands.size() > 1 && !expression.operations.empty())
  {
    throw std::logic_error("Error: wrong expression");
  }
  return expression.operands.pop().value;
}

std::string khoroshkin::getToken(const std::string & str, size_t & pos)
{
  skipWhitespace(str, pos);
  if (pos == str.length())
  {
    return "";
  }
  else if (std::isdigit(str[pos]))
  {
    return readOperand(str, pos);
  }
  else
  {
    return std::string(1, readOperation(str, pos));
  }
}

std::string khoroshkin::readOperand(std::string str, size_t & pos)
{
  std::string result = "";
  while (pos < str.length() && std::isdigit(str[pos]))
  {
    result += str[pos++];
  }
  return result;
}

char khoroshkin::readOperation(std::string str, size_t & pos)
{
  return str[pos++];
}

void khoroshkin::skipWhitespace(std::string str, size_t & pos)
{
  if (pos < str.length() && str[pos] == ' ')
  {
    pos++;
  }
}
