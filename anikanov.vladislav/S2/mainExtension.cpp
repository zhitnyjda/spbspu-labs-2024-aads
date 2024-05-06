#include "mainExtension.hpp"

#include <iostream>
#include <limits>
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
    auto oper = operators.top();
    if (oper->isBracket()) {
      throw std::invalid_argument("Invalid expression");
    }
    output.push(operators.top());
    operators.pop();
  }

  return output;
}

long long calculate(anikanov::Queue< std::shared_ptr< anikanov::ElementOfExpression > > &postfix)
{
  using namespace anikanov;
  Stack< std::shared_ptr< ElementOfExpression > > stack;

  while (!postfix.isEmpty()) {
    auto element = postfix.front();
    postfix.pop();

    if (element->isNumber()) {
      stack.push(element);
    } else {
      auto operation = std::dynamic_pointer_cast< Operation >(element);

      if (stack.getSize() < 2) {
        throw std::invalid_argument("Invalid expression");
      }

      auto right = std::dynamic_pointer_cast< Operand >(stack.top())->getValue();
      stack.pop();
      auto left = std::dynamic_pointer_cast< Operand >(stack.top())->getValue();
      stack.pop();
      long long result = 0;

      if (operation->getValue() == "+") {
        if (left > 0 && right > std::numeric_limits< long long >::max() - left) {
          throw std::overflow_error("Overflow error");
        }
        result = left + right;
      } else if (operation->getValue() == "-") {
        if (left < 0 && right > std::numeric_limits< long long >::max() + left + 1) {
          throw std::underflow_error("Underflow error");
        }
        result = left - right;
      } else if (operation->getValue() == "*") {
        if (left != 0 && right > std::numeric_limits< long long >::max() / left) {
          throw std::overflow_error("Overflow error");
        }
        result = left * right;
      } else if (operation->getValue() == "/") {
        if (right == 0) {
          throw std::invalid_argument("Division by zero");
        }
        result = left / right;
      } else if (operation->getValue() == "%") {
        if (right == 0) {
          throw std::invalid_argument("Division by zero");
        }
        result = (left % right + right) % right;
      }

      stack.push(std::make_shared< Operand >(result));
    }
  }

  if (stack.getSize() != 1) {
    throw std::invalid_argument("Invalid expression");
  }

  return std::dynamic_pointer_cast< Operand >(stack.top())->getValue();
}
