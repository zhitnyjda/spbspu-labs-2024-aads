#ifndef STACK_HPP
#define STACK_HPP
#include "List.hpp"

namespace taskaev
{
  template < typename T >
  class Stack
  {
  public:
    Stack();
    ~Stack() = default;
    void push(const T& value);
    void pop();
    bool isEmpty() const noexcept;
    T& top();
  private:
    List< T > container;
  };
}

template < typename T >
taskaev::Stack< T >::Stack():
  container(List< T >())
{}

template < typename T >
void taskaev::Stack< T >::push(const T& value)
{
  container.pushFront(value);
}

template < typename T >
void taskaev::Stack< T >::pop()
{
  container.popFront();
}

template < typename T >
bool taskaev::Stack< T >::isEmpty() const noexcept
{
  return container.isEmpty();
}

template < typename T >
T& taskaev::Stack< T >::top()
{
  return container.front();
}


#endif
