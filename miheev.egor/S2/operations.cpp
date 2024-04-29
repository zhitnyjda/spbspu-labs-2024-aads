#include "operations.hpp"

miheev::Operation::Operation(char op):
  operation(op)
{
  if (op == '+' || op == '-')
  {
    priority_ = 1;
  }
  else if (op == '*' || op == '/')
  {
    priority_ = 2;
  }
  else
  {
    priority_ = 0;
  }
}

bool miheev::Operation::operator<(const miheev::Operation& rhs)
{
  return priority_ < rhs.priority_;
}

bool miheev::Operation::operator<=(const miheev::Operation& rhs)
{
  return priority_ <= rhs.priority_;
}

bool miheev::Operation::operator==(const miheev::Operation& rhs)
{
  return priority_ == rhs.priority_;
}

bool miheev::Operation::operator>=(const miheev::Operation& rhs)
{
  return priority_ >= rhs.priority_;
}

bool miheev::Operation::operator>(const miheev::Operation& rhs)
{
  return priority_ > rhs.priority_;
}