#include <string>
#include "function.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "IdentifierMath.hpp"

namespace taskaev
{
  void inputMathValue(Queue< IdentifierMath >& queue, std::string mathValue)
  {
    std::string item;
    size_t i = 0;
    while( i < mathValue.length()) {
      if (mathValue[i] != ' ') {
        item += mathValue[i];
      }
      else {
        queue.push((IdentifierMath(item)));
        item = "";
      }
      i++;
    }
    queue.push(IdentifierMath(item));
  }

  void convertToPostfix(Queue< IdentifierMath >& queue, Queue< IdentifierMath >& postfix, Stack< IdentifierMath >& stack)
  {
    while (!queue.isEmpty()) {
      if (queue.front().types == operand)
      {
        postfix.push(queue.front());
        queue.pop();
      }
      else if (queue.front().types == operation)
      {
        stack.push(queue.front());
        queue.pop();
      }
      else if (queue.front().types == openParantheses)
      {
        stack.push(queue.front());
        queue.pop();
      }
      else if (queue.front().types == closedParantheses)
      {
        while (stack.top().types != openParantheses) {
          postfix.push(stack.top());
          stack.pop();
        }
        stack.pop();
        queue.pop();
      }
    }
    while (!stack.isEmpty())
    {
      postfix.push(stack.top());
      stack.pop();
    }
  }

  long long calculate(Queue< IdentifierMath >& postfix)
  {
    Stack< long long > result;
    while (!postfix.isEmpty()) {
      if (postfix.front().types == operand)
      {
        result.push(postfix.front().data);
      }
      else {
        long long operand = result.top();
        result.pop();
        if (postfix.front().data == '+')
        {
          operandOne += result.top();
        }
        else if (postfix.front().data == '-')
        {
          operandOne = result.top() - operandOne;
        }
        else if (postfix.front().data == '*')
        {
          operandOne *= result.top();
        }
        else if (postfix.front().data == '/')
        {
          operandOne = result.top() / operandOne;
        }
        else
        {
          operandOne = result.top() % operandOne;
        }
        result.pop();
        result.push(operandOne);
      }
      postfix.pop();
    }
    return result.top();
  }
}
