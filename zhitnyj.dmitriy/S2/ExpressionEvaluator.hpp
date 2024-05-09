#ifndef EXPRESSION_EVALUATOR_HPP
#define EXPRESSION_EVALUATOR_HPP

#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include "Queue.hpp"
#include "Stack.hpp"
#include "ExpressionItem.hpp"
#include "Operand.hpp"
#include "Operator.hpp"

class ExpressionEvaluator
{
public:
    static void parseExpression(Queue< std::shared_ptr< ExpressionItem>>& queue, const std::string& expression)
    {
      std::string token;
      for (size_t i = 0; i < expression.length(); ++i)
      {
        char c = expression[i];
        if (std::isspace(c))
        {
          if (!token.empty())
          {
            if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1])))
            {
              queue.push(std::make_shared< Operand >(std::stoll(token)));
            }
            else if (token.size() == 1 && std::string("+-*/%()").find(token[0]) != std::string::npos)
            {
              queue.push(std::make_shared< Operator >(token[0]));
            }
            else
            {
              throw std::runtime_error("Invalid token in expression: " + token);
            }
            token.clear();
          }
        }
        else
        {
          token += c;
        }
      }

      if (!token.empty())
      {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1])))
        {
          queue.push(std::make_shared< Operand >(std::stoll(token)));
        }
        else if (token.size() == 1 && std::string("+-*/%()").find(token[0]) != std::string::npos)
        {
          queue.push(std::make_shared< Operator >(token[0]));
        }
        else
        {
          throw std::runtime_error("Invalid token in expression: " + token);
        }
      }
    }

    static Queue< std::shared_ptr< ExpressionItem>> toPostfix(Queue< std::shared_ptr< ExpressionItem>>& infixQueue)
    {
      Stack< std::shared_ptr< ExpressionItem>> operatorStack;
      Queue< std::shared_ptr< ExpressionItem>> postfixQueue;

      while (!infixQueue.empty())
      {
        std::shared_ptr< ExpressionItem > item = infixQueue.front();
        infixQueue.pop();

        auto operand = std::dynamic_pointer_cast< Operand >(item);
        auto operator_ = std::dynamic_pointer_cast< Operator >(item);

        if (operand)
        {
          postfixQueue.push(operand);
        }
        else if (operator_)
        {
          if (operator_->isLeftParenthesis())
          {
            operatorStack.push(operator_);
          }
          else if (operator_->isRightParenthesis())
          {
            while (!operatorStack.empty()
                && !std::dynamic_pointer_cast< Operator >(operatorStack.top())->isLeftParenthesis())
            {
              postfixQueue.push(operatorStack.top());
              operatorStack.pop();
            }
            operatorStack.pop();
          }
          else
          {
            while (!operatorStack.empty()
                && std::dynamic_pointer_cast< Operator >(operatorStack.top())->precedence() >= operator_->precedence()
                &&
                    !std::dynamic_pointer_cast< Operator >(operatorStack.top())->isLeftParenthesis())
            {
              postfixQueue.push(operatorStack.top());
              operatorStack.pop();
            }
            operatorStack.push(operator_);
          }
        }
      }

      while (!operatorStack.empty())
      {
        postfixQueue.push(operatorStack.top());
        operatorStack.pop();
      }

      return postfixQueue;
    }

    static long long evaluateExpression(Queue< std::shared_ptr< ExpressionItem>>& postfixQueue)
    {
      Stack< long long > evaluationStack;

      while (!postfixQueue.empty())
      {
        std::shared_ptr< ExpressionItem > item = postfixQueue.front();
        postfixQueue.pop();

        if (auto operand = std::dynamic_pointer_cast< Operand >(item))
        {
          evaluationStack.push(operand->getValue());
        }
        else if (auto op = std::dynamic_pointer_cast< Operator >(item))
        {
          if (evaluationStack.size() < 2)
          {
            throw std::runtime_error("Insufficient values in the expression for operation");
          }
          long long right = evaluationStack.top();
          evaluationStack.pop();
          long long left = evaluationStack.top();
          evaluationStack.pop();
          if (op->getOperator() == '+' && (left > (std::numeric_limits< long long >::max() - right)))
          {
            throw std::overflow_error("There was an overflow error!");
          }
          else if (op->getOperator() == '-' && (left > (std::numeric_limits< long long >::max() + right)))
          {
            throw std::overflow_error("There was an overflow error!");
          }
          else if (op->getOperator() == '*' && (left > (std::numeric_limits< long long >::max() / right)))
          {
            throw std::overflow_error("There was an overflow error!");
          }
          else if (op->getOperator() == '/' && (left > (std::numeric_limits< long long >::max() * right)))
          {
            throw std::overflow_error("There was an overflow error!");
          }
          long long result = op->applyOp(left, right);
          evaluationStack.push(result);
        }
        else
        {
          throw std::runtime_error("Invalid expression item encountered");
        }
      }

      if (evaluationStack.size() != 1)
      {
        throw std::runtime_error("The expression does not reduce to a single value");
      }

      return evaluationStack.top();
    }
};

#endif
