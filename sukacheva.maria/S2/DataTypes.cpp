#include "DataTypes.hpp"
#include <string>

sukacheva::Bracket::Bracket(char bracket_):
  bracket(bracket_)
{}


bool sukacheva::Bracket::ifBracketIsOpen() const
{
  return bracket == '(';
}

bool sukacheva::Bracket::ifBracketIsClose() const
{
  return bracket == ')';
}

sukacheva::Operand::Operand(long long value_):
  value(value_)
{}

sukacheva::Operand sukacheva::Operand::operator+(const Operand& val)
{
  Operand result = val.value + value;
  return result;
}

sukacheva::Operand sukacheva::Operand::operator-(const Operand& val)
{
  Operand result = value - val.value;
  return result;
}

sukacheva::Operand sukacheva::Operand::operator*(const Operand& val)
{
  Operand result = value * val.value;
  return result;
}

sukacheva::Operand sukacheva::Operand::operator/(const Operand& val)
{
  Operand result = value / val.value;
  return result;
}

sukacheva::Operand sukacheva::Operand::operator%(const Operand& val)
{
  Operand result = (value % val.value) < 0 ? (value % val.value) + val.value : (value % val.value);
  return result;
}

sukacheva::Operation::Operation(char operation_) :
  operation(operation_)
{}

bool sukacheva::Operation::priorityOfOperation(Operation other)
{
  int priorityIndex1 = 1;
  int priorityIndex2 = 1;
  if (other.operation == '*' || other.operation == '/' || other.operation == '%')
  {
    priorityIndex1 = 2;
  }
  if (operation == '*' || operation == '/' || operation == '%')
  {
    priorityIndex2 = 2;
  }
  else if (operation == '(' || other.operation == '(')
  {
    return false;
  }
  return priorityIndex1 >= priorityIndex2;
}

bool sukacheva::ElementOfStatement::isBracket(std::string applicant) const noexcept
{
  return applicant == "(" || applicant == ")";
}

bool sukacheva::ElementOfStatement::isNumber(std::string applicant) const noexcept
{
  return !applicant.empty() && (applicant.find_first_not_of("0123456789") == applicant.npos);
}

bool sukacheva::ElementOfStatement::isBinaryOperations(std::string applicant) const noexcept
{
  return !applicant.empty() && (applicant.find_first_not_of("+-*/%") == applicant.npos);
}