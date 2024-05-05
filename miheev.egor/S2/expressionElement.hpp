#ifndef EXPRESSION_ELEMENT_HPP
#define EXPRESSION_ELEMENT_HPP

#include "operations.hpp"
#include "operands.hpp"
#include "string"

namespace miheev
{
  struct element_t
  {
  public:
    element_t();
    element_t(const element_t&);
    element_t& operator=(const element_t&);

    Operand getOperand() const;
    Operation getOperation() const;
    Parenthesis getParenthesis() const;
    std::string getType() const;

    void setOperand(const Operand& rhs);
    void setOperation(const Operation& rhs);
    void setParenthesis(const Parenthesis& rhs);
    void setType(std::string rhs);

  private:
    Operand operand;
    Operation operation;
    Parenthesis parenthesis;
    std::string type;
  };
}

#endif
