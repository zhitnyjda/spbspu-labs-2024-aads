#ifndef IDENTIFIERMATH_HPP
#define IDENTIFIERMATH_HPP
#include <stdexcept>
#include <string>
#include <cstring>

namespace taskaev
{
  enum mathType
  {
    operand,
    operation,
    openParantheses,
    closedParantheses
  };

  struct Operand
  {
    long long data;
  };

  struct Operation
  {
    char data;
  };

  struct IdentifierMath {
    mathType types;
    union
    {
      Operand operands;
      Operation operations;
      char parantheses;
    };
    IdentifierMath() = default;
    explicit IdentifierMath(const std::string& item)
    {
      if (!isValue(item))
      {
        throw std::invalid_argument(" SOS are you Ok?");
      }
      if (isdigit(item[0])) {
        types = operand;
        operands.data = std::stoll(item);
      }
      else if (isOperation(item[0])) {
        types = operation;
        operations.data = item[0];
      }
      else if ('(' == item[0]) {
        types = openParantheses;
        parantheses = item[0];
      }
      else
      {
        types = closedParantheses;
        parantheses = item[0];
      }
    }
    private:
      bool isValue(const std::string& item)
      {
        for (size_t i = 0; i < item.length(); i++) {
          if (!isdigit(item[i]) && (item.length() > 1)) {
            return false;
          }
        }
      }
      bool isOperation(char c)
      {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
      }
  };
}

#endif
