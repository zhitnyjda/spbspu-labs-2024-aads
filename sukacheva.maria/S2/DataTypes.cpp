#include "DataTypes.hpp"
#include <string>

sukacheva::Bracket::Bracket(char bracket_):
  bracket(bracket_)
{}

sukacheva::Bracket::Bracket(std::string value):
  bracket(*value.c_str())
{}

bool sukacheva::Bracket::ifBracketIsOpen() const noexcept
{
  return bracket == '(';
}

bool sukacheva::Bracket::ifBracketIsClose() const noexcept
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

sukacheva::Operation::Operation(std::string value):
  operation(*value.c_str())
{}

bool sukacheva::Operation::priorityOfOperation(ElementOfStatement other)
{
  int priorityIndex1 = 1;
  int priorityIndex2 = 1;
  if (other.applicant == "*" || other.applicant == "/" || other.applicant == "%")
  {
    priorityIndex1 = 2;
  }
  if (operation == '*' || operation == '/' || operation == '%')
  {
    priorityIndex2 = 2;
  }
  else if (operation == '(' || other.applicant == "(")
  {
    return false;
  }
  return priorityIndex1 >= priorityIndex2;
}

sukacheva::ElementOfStatement::ElementOfStatement(std::string applicant_):
  applicant(applicant_)
{}

bool sukacheva::ElementOfStatement::isBracket() const noexcept
{
  return applicant == "(" || applicant == ")";
}

bool sukacheva::ElementOfStatement::isNumber() const noexcept
{
  return !applicant.empty() && (applicant.find_first_not_of("0123456789") == applicant.npos);
}

bool sukacheva::ElementOfStatement::isBinaryOperations() const noexcept
{
  return !applicant.empty() && (applicant.find_first_not_of("+-*/%") == applicant.npos);
}
