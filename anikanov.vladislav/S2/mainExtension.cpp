#include "mainExtension.hpp"

#include <iostream>
#include <sstream>
#include "stack.hpp"
#include "elementOfExpression.hpp"
#include "bracket.hpp"
#include "operand.hpp"


bool checkPriority(const elementType &first, const std::shared_ptr< anikanov::Operation > &second)
{
  if (first->isBracket()) {
    return 0 >= second->getPriority();
  }
  auto operation = std::dynamic_pointer_cast< anikanov::Operation >(first);
  return operation->getPriority() >= std::dynamic_pointer_cast< anikanov::Operation >(second)->getPriority();
}

bool checkForward(const elementType &element)
{
  if (!element->isBracket()) {
    return false;
  }
  return std::dynamic_pointer_cast< anikanov::Bracket >(element)->isForward();
}


anikanov::Queue< std::shared_ptr< anikanov::ElementOfExpression > > toPostfix(const std::string &expression)
{
  using namespace anikanov;
  Stack< std::shared_ptr< ElementOfExpression > > operators;
  Queue< std::shared_ptr< ElementOfExpression > > output;
  std::stringstream ss(expression);
  std::string token;

  while (ss >> token) {
    if (isdigit(token[0])) {
      output.push(std::make_shared< Operand >(token));
    } else if (token[0] == '(') {
      operators.push(std::make_shared< Bracket >(token));
    } else if (token[0] == ')') {
      if (operators.isEmpty()) {
        throw std::invalid_argument("Invalid expression");
      }
      while (!operators.isEmpty() && !checkForward(operators.top())) {
        output.push(operators.top());
        operators.pop();
      }
      operators.pop();
    } else {
      std::shared_ptr< Operation > operation = std::make_shared< Operation >(token);
      while (!operators.isEmpty() && checkPriority(operators.top(), operation)) {
        output.push(operators.top());
        operators.pop();
      }
      operators.push(operation);
    }
  }

  while (!operators.isEmpty()) {
    output.push(operators.top());
    operators.pop();
  }

  return output;
}
