#ifndef STACK_HPP
#define STACK_HPP
#include "List.hpp"

namespace taskaev
{
  template < typename T >
  class Stack
  {
  public:
    Stack() = default;
    ~Stack() = default;
    void push(const T& value);
    void pop();
    bool isEmpty() const noexcept;
    T& top();
  private:
    List< T > greenfield;
  };
}

template < typename T >
void taskaev::Stack< T >::push(const T& value)
{
  greenfield.pushFront(value);
}

template < typename T >
void taskaev::Stack< T >::pop()
{
  greenfield.popFront();
}

template < typename T >
bool taskaev::Stack< T >::isEmpty() const noexcept
{
  return greenfield.isEmpty();
}

template < typename T >
T& taskaev::Stack< T >::top()
{
  return greenfield.front();
}


#endif
