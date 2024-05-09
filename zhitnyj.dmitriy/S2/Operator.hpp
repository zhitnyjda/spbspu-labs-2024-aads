#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "ExpressionItem.hpp"
#include <stdexcept>

class Operator : public ExpressionItem
{
public:
    explicit Operator(char op) : operator_(op)
    {
      if (!isOperator(op))
      {
        throw std::invalid_argument("Unsupported operator");
      }
    }

    bool isLeftParenthesis() const
    {
      return operator_ == '(';
    }

    bool isRightParenthesis() const
    {
      return operator_ == ')';
    }

    char getOperator() const
    {
      return operator_;
    }

    int precedence() const
    {
      if (operator_ == '+' || operator_ == '-')
      {
        return 1;
      }
      else if (operator_ == '*' || operator_ == '/' || operator_ == '%')
      {
        return 2;
      }
      else if (operator_ == '(' || operator_ == ')')
      {
        return 0;
      }
      else
      {
        throw std::runtime_error("Unsupported operator");
      }
    }

    long long applyOp(long long a, long long b) const
    {
      if (operator_ == '+')
      {
        return a + b;
      }
      else if (operator_ == '-')
      {
        return a - b;
      }
      else if (operator_ == '*')
      {
        return a * b;
      }
      else if (operator_ == '/')
      {
        if (b == 0)
        {
          throw std::runtime_error("Division by zero");
        }
        return a / b;
      }
      else if (operator_ == '%')
      {
        if (b == 0)
        {
          throw std::runtime_error("Modulo by zero")
        }
        if (a < 0)
        {
          return a % b + abs(a);
        }
        return a % b;
      }
      else
      {
        throw std::invalid_argument("Invalid operation");
      }
    }

private:
    char operator_;

    static bool isOperator(char c)
    {
      return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')';
    }
};

#endif
