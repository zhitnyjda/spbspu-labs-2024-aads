#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

namespace miheev
{
  class Operation
  {
  public:
    Operation(char);
    bool operator<(const Operation& rhs);
    bool operator<=(const Operation& rhs);
    bool operator==(const Operation& rhs);
    bool operator>=(const Operation& rhs);
    bool operator>(const Operation& rhs);
    char operation;
  private:
    int priority_;
  };

  struct Parenthesis
  {
    char parenthesis;
  };
}

#endif