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
    result.operand.value = s[0];
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
  while (line != "")
  {
    miheev::element_t current = getElement(line);
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
          queue.push(stack.drop());
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
        queue.push(stack.drop());
      }
      stack.push(current);
    }
  }
  return queue;
}

long long miheev::calcLine(std::string line)
{
  miheev::Stack< miheev::element_t > stack;
  Queue< element_t > posfix = miheev::lineToPosfix(line);
  std::cout << posfix.front().type << '\n';
  return 0; // Затычка - TODO: исправить
}

// miheev::Stack< long long > miheev::processInput(std::istream& in)
// {
//   Stack< long long > results;
//   Queue< element_t > postfix;
//   std::string line = "";
//   while (!in.eof())
//   {
//     std::getline(in, line);
//     postfix = miheev::lineToPosfix(line);
//   }
// }