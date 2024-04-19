#include "functions.hpp"

using ListStr = nikiforov::List< std::string >;

void nikiforov::convertToPostfix(std::string str, ListStr& Queue)
{
  ListStr Stack;
  std::string elemSeq = "";
  size_t count1 = str.find(" ");

  while (count1 != std::string::npos)
  {
    count1 = str.find(" ");
    elemSeq = str.substr(0, str.find_first_of(" ", 0));
    str = str.substr(str.find(" ") + 1);

    if (isdigit(elemSeq[0]))
    {
      Queue.push_back(elemSeq);
    }
    else
    {
      if (elemSeq == "(")
      {
        Stack.push_back(elemSeq);
      }
      else if (elemSeq == ")")
      {
        while (Stack.back() != "(")
        {
          Queue.push_back(Stack.back());
          Stack.pop_back();
        }
        Stack.pop_back();
      }
      else if (!Stack.is_empty())
      {
        if (nikiforov::calculationPriority(elemSeq) <= nikiforov::calculationPriority(Stack.back()))
        {
          Queue.push_back(Stack.back());
          Stack.pop_back();
          Stack.push_back(elemSeq);
        }
        else
        {
          Stack.push_back(elemSeq);
        }
      }
      else
      {
        Stack.push_back(elemSeq);
      }
    }
  }
  while (!Stack.is_empty() && Stack.back() != "(")
  {
    Queue.push_back(Stack.back());
    Stack.pop_back();
  }
}

void nikiforov::calculation(ListStr& Postfix, nikiforov::List< long long >& Result)
{
  std::string elemSeq = "";
  nikiforov::List< long long > Queue;

  while (!Postfix.is_empty())
  {
    elemSeq = Postfix.front();
    if (isdigit(elemSeq[0]))
    {
      Queue.push_back(stoll(Postfix.front()));
    }
    else
    {
      operation(elemSeq, Queue);
    }
    Postfix.pop_front();
  }
  if (!Queue.is_empty())
  {
    Result.push_back(Queue.back());
  }
}

void nikiforov::operation(std::string operand, nikiforov::List< long long >& Queue)
{
  long long rNum = Queue.back();
  Queue.pop_back();
  long long lNum = Queue.back();
  Queue.pop_back();

  if (operand == "+")
  {
    Queue.push_back(lNum + rNum);
  }
  else if (operand == "-")
  {
    Queue.push_back(lNum - rNum);
  }
  else if (operand == "/")
  {
    Queue.push_back(lNum / rNum);
  }
  else if (operand == "*")
  {
    Queue.push_back(lNum * rNum);
  }
  else if (operand == "%")
  {
    Queue.push_back(lNum % rNum);
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
  else if (elemSeq == "(")
  {
    return 0;
  }
  else
  {
    throw std::invalid_argument("Error: invalid operand");
  }
}
