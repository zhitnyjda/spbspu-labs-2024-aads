#include "DataProcessing.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "Stack.hpp"
#include "Queue.hpp"

sukacheva::stackOfQueue sukacheva::inputStatement(std::istream& in)
{
  std::string name = "";
  stackOfQueue result;
  while (in) {
    Queue< std::string > temp;
    result.push(temp);
    while (in >> name && (isNumber(name) || isBinaryOperations(name))) {
      result.top().push(name);
    }
  }
  return result;
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
    if (infix.front() == "(") {
      temp.push(infix.front());
      infix.pop();
    }
    else if (infix.front() == ")") {
      while (temp.top() != "(") {
        postfix.push(temp.top());
        temp.pop();
      }
      infix.pop();
      temp.pop();
    }
    else if (isNumber(infix.front())) {
      postfix.push(infix.front());
      infix.pop();
    }
    else if (isBinaryOperations(infix.front())) {
      temp.push(infix.front());
      infix.pop();
    }
    else {
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

size_t sukacheva::calculate(Queue< std::string >& postfix)
{
  return size_t();
}