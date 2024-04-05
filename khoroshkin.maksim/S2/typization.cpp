#include "typization.hpp"

khoroshkin::Operator::Operator() :
  operation('0')
{}

khoroshkin::Operator::Operator(char oper) :
  operation(oper)
{}

khoroshkin::Operand::Operand() :
  value(0)
{}

khoroshkin::Operand::Operand(long long oper) :
  value(oper)
{}

void khoroshkin::Postfix::popOperation()
{
  Operand secondOperand = operands.pop();
  Operand firstOperand = operands.pop();
  
  if (operations.top() == '+')
  {
    operands.push(firstOperand + secondOperand);
  }
  else if (operations.top() == '-')
  {
    operands.push(firstOperand - secondOperand);
  }
  else if (operations.top() == '*')
  {
    operands.push(firstOperand * secondOperand);
  }
  else if (operations.top() == '/')
  {
    operands.push(firstOperand / secondOperand);
  }
  else if (operations.top() == '%')
  {
    operands.push(firstOperand % secondOperand);
  }
  operations.pop();
}

bool khoroshkin::Operator::operator==(const char & rhs) const
{
  return operation == rhs;
}

bool khoroshkin::Operator::operator!=(const char & rhs) const
{
  return operation != rhs;
}

khoroshkin::Operand khoroshkin::Operand::operator+(const Operand & rhs)
{
  Operand result;
  result.value = value + rhs.value;
  return result;
}

khoroshkin::Operand khoroshkin::Operand::operator-(const Operand & rhs)
{
  Operand result;
  result.value = value - rhs.value;
  return result;
}

khoroshkin::Operand khoroshkin::Operand::operator*(const Operand & rhs)
{
  Operand result;
  result.value = value * rhs.value;
  return result;
}

khoroshkin::Operand khoroshkin::Operand::operator/(const Operand & rhs)
{
  Operand result;
  result.value = value / rhs.value;
  return result;
}

khoroshkin::Operand khoroshkin::Operand::operator%(const Operand & rhs)
{
  Operand result;
  result.value = value % rhs.value;
  return result;
}

bool khoroshkin::Postfix::canPop(Operator oper)
{
  if (operations.empty())
  {
    return false;
  }
  int priorNewOper = oper.getPriority();
  int priorOldOper = operations.top().getPriority();
  return priorNewOper >= 0 && priorOldOper >= 0 && priorNewOper >= priorOldOper;
}

int khoroshkin::Operator::getPriority()
{
  if (operation == '(')
  {
    return -1;
  }
  else if (operation == '*' or operation == '/' or operation == '%')
  {
    return 1;
  }
  else if (operation == '+' or operation == '-')
  {
    return 2;
  }
  throw std::logic_error("Invalid operation");
}
