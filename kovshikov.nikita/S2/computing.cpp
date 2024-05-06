#include "computing.hpp"
#include <cstring>

void kovshikov::readData(std::istream& in, Queue< std::string >& allData)
{
  while(!in.eof())
  {
    std::string expression = "";
    std::getline(in, expression);
    if(!expression.empty())
    {
      allData.push(expression);
    }
  }
}

void kovshikov::separateElements(std::string str, Queue< std::string >& queue)
{
  std::string temp = "";
  size_t sizeStr = str.length();
  for(size_t i = 0; i < sizeStr; i++)
  {
    if(str[i] != ' ')
    {
      temp += str[i];
    }
    else
    {
      queue.push(temp);
      temp = "";
    }
  }
  queue.push(temp);
}

int kovshikov::getPriority(char c)
{
  if (c == '/' || c == '*' || c == '%')
  {
    return 2;
  }
  else if( c == '+' || c == '-')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

bool kovshikov::isDigit(std::string str)
{
  size_t size = str.length();
  for(size_t i = 0; i < size; i++)
  {
    if(!std::isdigit(str[i]))
    {
      return false;
    }
  }
  return true;
}

void kovshikov::getPostfix(Queue< std::string >& oldQ, Queue< std::string >& newQ)
{
  Stack< std::string > stack;
  std::string element = "";
  size_t size = oldQ.getSize();
  for(size_t i = 0; i < size; i++)
  {
    element = oldQ.front();
    oldQ.pop();
    if(isDigit(element))
    {
      newQ.push(element);
    }
    else if(element[0] == '(')
    {
      stack.push(element);
    }
    else if(element[0] == ')')
    {
      while(stack.top()[0] != '(')
      {
        newQ.push(stack.top());
        stack.pop();
      }
      stack.pop();
    }
    else
    {
      while(!stack.isEmpty() && getPriority(element[0]) <= getPriority(stack.top()[0]))
      {
        newQ.push(stack.top());
        stack.pop();
      }
      stack.push(element);
    }
  }
  while(!stack.isEmpty())
  {
    newQ.push(stack.top());
    stack.pop();
  }
}
