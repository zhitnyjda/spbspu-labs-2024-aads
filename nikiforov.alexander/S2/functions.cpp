#include "functions.hpp"

void nikiforov::convertToPostfix(std::string str, Queue< dataTypes >& queue)
{
  Stack< dataTypes > stack;
  size_t count1 = str.find(" ");
  nikiforov::dataTypes elemSeq;

  while (count1 != std::string::npos)
  {
    count1 = str.find(" ");
    elemSeq = getType(str);

    if (elemSeq.type_ == operand)
    {
      queue.push_back(elemSeq);
    }
    else
    {
      if (elemSeq.type_ == bracket)
      {
        if (elemSeq.data_ == "(")
        {
          stack.push_back(elemSeq);
        }
        else
        {
          while (stack.back().data_ != "(")
          {
            queue.push_back(stack.back());
            stack.pop_back();
          }
          stack.pop_back();
        }
      }
      else if (!stack.is_empty())
      {
        if (nikiforov::calculationPriority(elemSeq.data_) <= nikiforov::calculationPriority(stack.back().data_))
        {
          queue.push_back(stack.back());
          stack.pop_back();
          stack.push_back(elemSeq);
        }
        else
        {
          stack.push_back(elemSeq);
        }
      }
      else
      {
        stack.push_back(elemSeq);
      }
    }
  }
  while (!stack.is_empty() && stack.back().data_ != "(")
  {
    queue.push_back(stack.back());
    stack.pop_back();
  }
}

void nikiforov::calculation(Queue< dataTypes >& Postfix, nikiforov::List< long long >& Result)
{
  nikiforov::Stack< long long > stack;
  nikiforov::dataTypes elemSeq;
  while (!Postfix.is_empty())
  {
    elemSeq = Postfix.front();
    if (elemSeq.type_ == operand)
    {
      stack.push_back(stoll(elemSeq.data_));
    }
    else
    {
      operations(elemSeq.data_, stack);
    }
    Postfix.pop_front();
  }
  if (!stack.is_empty())
  {
    Result.push_back(stack.back());
  }
}

void nikiforov::operations(std::string operand, nikiforov::Stack< long long >& stack)
{
  long long rNum = stack.back();
  stack.pop_back();
  long long lNum = stack.back();
  stack.pop_back();

  long long minValue = std::numeric_limits< long long >::min();
  long long maxValue = std::numeric_limits< long long >::max();

  if (operand == "+")
  {
    if (rNum > 0 && lNum > 0 && (rNum > maxValue - lNum))
    {
      throw std::overflow_error("Error: overflow");
    }
    if (rNum < 0 && lNum < 0 && (rNum < maxValue - lNum))
    {
      throw std::overflow_error("Error: overflow");
    }
    stack.push_back(lNum + rNum);
  }
  else if (operand == "-")
  {
    if (lNum > 0 && rNum < 0 && (lNum > std::numeric_limits< long long >::max() + rNum))
    {
      throw std::overflow_error("Error: overflow");
    }
    if (lNum < 0 && rNum > 0 && (lNum < std::numeric_limits< long long >::min() + rNum))
    {
      throw std::overflow_error("Error: overflow");
    }
    stack.push_back(lNum - rNum);
  }
  else if (operand == "/")
  {
    stack.push_back(lNum / rNum);
  }
  else if (operand == "*")
  {
    if (((lNum > 0 && rNum > 0) || (lNum < 0 && rNum < 0)) && (abs(rNum) > abs(maxValue / lNum)))
    {
      throw std::overflow_error("Error: overflow");
    }
    if (((lNum > 0 && rNum < 0) || (lNum < 0 && rNum > 0)) && (abs(rNum) > abs(minValue / lNum)))
    {
      throw std::overflow_error("Error: overflow");
    }
    stack.push_back(lNum * rNum);
  }
  else if (operand == "%")
  {
    stack.push_back(lNum % rNum);
  }
  else
  {
    throw std::invalid_argument("Error: invalid operand");
  }
}

size_t nikiforov::calculationPriority(std::string elemSeq)
{
  if (elemSeq == "+" || elemSeq == "-")
  {
    return 1;
  }
  else if (elemSeq == "*" || elemSeq == "/" || elemSeq == "%")
  {
    return 2;
  }
  else
  {
    return 0;
  }
}
