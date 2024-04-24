#ifndef DATATYPES_HPP
#define DATATYPES_HPP
#include <string>
#include "Stack.hpp"

namespace sukacheva
{
  struct ElementOfStatement
  {
    ~ElementOfStatement() = default;
    ElementOfStatement() = default;
    ElementOfStatement(std::string applicant_);
    bool isBracket() const noexcept;
    bool isNumber() const noexcept;
    bool isBinaryOperations() const noexcept;

    std::string applicant;
  };

  struct Bracket : public ElementOfStatement
  {
    Bracket(char bracket_);
    Bracket(std::string value);
    bool ifBracketIsOpen() const noexcept;
    bool ifBracketIsClose() const noexcept;

    char bracket;
  };

  struct Operand : public ElementOfStatement
  {
    Operand(long long value_);

    Operand operator+(const Operand& val);
    Operand operator-(const Operand& val);
    Operand operator*(const Operand& val);
    Operand operator/(const Operand& val);
    Operand operator%(const Operand& val);

    long long value;
  };

  struct Operation : public ElementOfStatement
  {
    Operation(char operation_);
    Operation(std::string value);

    bool priorityOfOperation(ElementOfStatement other);

    char operation;
  };

  struct Postfix
  {
    Stack< Operation > operations;
    Stack< Operand > operands;
  };
}

#endif
