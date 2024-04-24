#ifndef DATATYPES_HPP
#define DATATYPES_HPP

namespace sukacheva
{
  struct ElementOfStatement
  {
    ~ElementOfStatement() = default;
    bool isBracket(std::string applicant) const noexcept;
    bool isNumber(std::string applicant) const noexcept;
    bool isBinaryOperations(std::string applicant) const noexcept;
  };

  struct Bracket : public ElementOfStatement
  {
    Bracket(char bracket_);
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

    bool priorityOfOperation(Operation other);

    char operation;
  };
}

#endif