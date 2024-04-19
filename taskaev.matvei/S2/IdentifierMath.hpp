#ifndef IDENTIFIERMATH_H
#define IDENTIFIERMATH_H
#include <stdexcept>
#include <string>

namespace taskaev
{
  enum mathType
  {
    operand,
    operation,
    openParantheses,
    closedParantheses
  };
  struct IdentifierMath {
    mathType types;
    long long data;
    IdentifierMath() = default;
    explicit IdentifierMath(const std::string& item)
    {
      for (size_t i = 0; i < unit.length(); i++) {
        if (!isdigit(item[i]) && (item.length() > 1)) {
          throw std::invalid_argument(" SOS are you Ok? ");
        }
      }
      if (isdigit(item[0])) {
        types = operand;
        data = std::stoll(item);
      }
      else if (strchr("+-*/%", item[0])) {
        types = operation;
        data = item[0];
      }
      else if ('(' == item[0]) {
        types = openParantheses;
        data = item[0];
      }
      else
      {
        types = closedParantheses;
        data = item[0];
      }
    }
  };
}

#endif
