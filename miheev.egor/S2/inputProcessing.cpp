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
    result.setOperation(s[0]);
    result.setType("operation");
  }
  else if (s == "(")
  {
    result.setParenthesis(miheev::Parenthesis{s[0]});
    result.setType("parenthesis");
  }
  else if (s == ")")
  {
    result.setParenthesis(miheev::Parenthesis{')'});
    result.setType("parenthesis");
  }
  else
  {
    result.setOperand(miheev::Operand(stoll(s)));
    result.setType("operand");
  }
  return result;
}

miheev::element_t miheev::getElement(std::string& s)
{
  std::string symbol = getSymbol(s);
  miheev::element_t element = miheev::convertToElement(symbol);
  return element;
}

bool isOpeningParenthesisOnTop(const miheev::Stack< miheev::element_t >& stack)
{
  if (stack.empty())
  {
    return false;
  }
  if (stack.top().getType() != "parenthesis")
  {
    return false;
  }
  if (stack.top().getParenthesis().parenthesis != '(')
  {
    return false;
  }
  return true;
}

bool shouldPushOpToStack(const miheev::Stack< miheev::element_t >& stack, const miheev::element_t& curr)
{
  if (stack.empty())
  {
    return true;
  }
  if (stack.top().getType() != "operation")
  {
    return true;
  }
  if (curr.getOperation() < stack.top().getOperation())
  {
    return true;
  }
  return false;
}

miheev::Queue< miheev::element_t > miheev::lineToPosfix(std::string line)
{
  Stack< miheev::element_t > stack;
  Queue< miheev::element_t > queue;
  miheev::element_t current;
  while (line != "")
  {
    current = getElement(line);
    if (current.getType() == "parenthesis")
    {
      if (current.getParenthesis().parenthesis == '(')
      {
        stack.push(current);
      }
      else
      {
        while (!isOpeningParenthesisOnTop(stack))
        {
          miheev::element_t temp = stack.drop();
          queue.push(temp);
        }
        stack.pop();
      }
    }
    else if (current.getType() == "operand")
    {
      queue.push(current);
    }
    else if (current.getType() == "operation")
    {
      while (!shouldPushOpToStack(stack, current))
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
    std::cout << q.drop().getType() << ' ';
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
    if (current.getType() == "operand")
    {
      stack.push(current.getOperand());
    }
    else if(current.getType() == "operation")
    {
      Operand rhs = stack.drop();
      Operand lhs = stack.drop();
      stack.push(current.getOperation().implement(lhs, rhs));
    }
    else
    {
      throw std::logic_error("Unsupported expression element occured while calculating expr\n");
    }
  }
  if (stack.size() > 1)
  {
    throw std::runtime_error("not all operands are used. check your expression");
  }
  return stack.top().getValue();
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
