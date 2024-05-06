#include "functions.hpp"

void nikiforov::convertToPostfix(std::string str, Queue< std::string >& queue)
{
  Stack< std::string > stack;
  size_t count1 = str.find(" ");
  nikiforov::dataTypes elemSeq;

  while (count1 != std::string::npos)
  {
    count1 = str.find(" ");
    elemSeq = getType(str);

    if (elemSeq.type_ == operand)
    {
      queue.push_back(elemSeq.data_);
    }
    else
    {
      if (elemSeq.type_ == bracket)
      {
        if (elemSeq.data_ == "(")
        {
          stack.push_back(elemSeq.data_);
        }
        else
        {
          while (stack.back() != "(")
          {
            queue.push_back(stack.back());
            stack.pop_back();
          }
          stack.pop_back();
        }
      }
      else if (!stack.is_empty())
      {
        if (nikiforov::calculationPriority(elemSeq.data_) <= nikiforov::calculationPriority(stack.back()))
        {
          queue.push_back(stack.back());
          stack.pop_back();
          stack.push_back(elemSeq.data_);
        }
        else
        {
          stack.push_back(elemSeq.data_);
        }
      }
      else
      {
        stack.push_back(elemSeq.data_);
      }
    }
  }
  while (!stack.is_empty() && stack.back() != "(")
  {
    queue.push_back(stack.back());
    stack.pop_back();
  }
}

void nikiforov::calculation(Queue< std::string >& Postfix, nikiforov::List< long long >& Result)
{
  std::string elemSeq = "";
  nikiforov::Stack< long long > stack;

  while (!Postfix.is_empty())
  {
    elemSeq = Postfix.front();
    if (isdigit(elemSeq[0]))
    {
      stack.push_back(stoll(Postfix.front()));
    }
    else
    {
      operations(elemSeq, stack);
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

  if (operand == "+")
  {
    stack.push_back(lNum + rNum);
  }
  else if (operand == "-")
  {
    stack.push_back(lNum - rNum);
  }
  else if (operand == "/")
  {
    stack.push_back(lNum / rNum);
  }
  else if (operand == "*")
  {
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
