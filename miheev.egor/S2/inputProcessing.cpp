#include "inputProcessing.hpp"
#include "expressionElement.hpp"
#include "queue.hpp"

namespace miheev
{
  std::string getSymbol(std::string&);
  element_t convertToElement(std::string);
  element_t getElement(std::string&);
  Queue< element_t > lineToPosfix(std::string line);
  long long calcLine(std::string);
  void printTypes(miheev::Queue< element_t >);
}

std::string miheev::getSymbol(std::string& s)
{
  std::string symbol = s.substr(0, s.find(" "));
  if (s.find(" ") == std::string::npos)
  {
    s = "";
  }
  else
  {
    s = s.substr(s.find(" ") + 1);
  }
  return symbol;
}

miheev::element_t miheev::convertToElement(std::string s)
{
  miheev::element_t result;
  if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%")
  {
    result.operation.operation = s[0];
    result.type = "operation";
  }
  else if (s == "(")
  {
    result.parenthesis.parenthesis = s[0];
    result.type = "parenthesis";
  }
  else if (s == ")")
  {
    result.parenthesis.parenthesis = ')';
    result.type = "parenthesis";
  }
  else
  {
    result.operand.value = stoll(s);
    result.type = "operand";
  }
  return result;
}

miheev::element_t miheev::getElement(std::string& s)
{
  std::string symbol = getSymbol(s);
  miheev::element_t element = miheev::convertToElement(symbol);
  return element;
}

miheev::Queue< miheev::element_t > miheev::lineToPosfix(std::string line)
{
  Stack< miheev::element_t > stack;
  Queue< miheev::element_t > queue;
  miheev::element_t current;
  while (line != "")
  {
    current = getElement(line);
    if (current.type == "parenthesis")
    {
      if (current.parenthesis.parenthesis == '(')
      {
        stack.push(current);
      }
      else
      {
        while (!(stack.top().type == "parenthesis" && stack.top().parenthesis.parenthesis == '('))
        {
          miheev::element_t temp = stack.drop();
          queue.push(temp);
        }
        stack.pop();
      }
    }
    else if (current.type == "operand")
    {
      queue.push(current);
    }
    else if (current.type == "operation")
    {
      while (stack.top().type == "operation" && current.operation >= stack.top().operation)
      {
        miheev::element_t temp = stack.drop();
        queue.push(temp);
      }
      stack.push(current);
    }
  }
  while (!stack.empty())
  {
    queue.push(stack.drop());
  }
  return queue;
}

void miheev::printTypes(miheev::Queue< miheev::element_t > q)
{
  while (!q.empty())
  {
    std::cout << q.drop().type << ' ';
  }
  std::cout << '\n';
}

long long miheev::calcLine(std::string line)
{
  miheev::Stack< Operand > stack;
  Queue< miheev::element_t > postfix = miheev::lineToPosfix(line);
  while (!postfix.empty())
  {
    miheev::element_t current = postfix.drop();
    if (current.type == "operand")
    {
      stack.push(current.operand);
    }
    else if(current.type == "operation")
    {
      Operand rhs = stack.drop();
      Operand lhs = stack.drop();
      stack.push(current.operation.implement(lhs, rhs));
    }
  }
  if (stack.size() > 1)
  {
    throw std::runtime_error("not all operands are used. check your expression");
  }
  return stack.top().value;
}

miheev::Stack< long long > miheev::processInput(std::istream& in)
{
  Stack< long long > results;
  Queue< element_t > postfix;
  std::string line = "";
  while (!in.eof())
  {
    std::getline(in, line);
    if (line != "")
    {
      results.push(miheev::calcLine(line));
    }
  }
  return results;
}
