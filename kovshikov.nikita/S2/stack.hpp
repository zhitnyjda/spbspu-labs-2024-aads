#ifndef STACK_HPP
#define STACK_HPP
#include "doublelist.hpp"

namespace kovshikov
{
  template< typename T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T > & s);
    Stack(Stack< T > && s);
    ~Stack() = default;

    void push(const Stack< T > val);
    
  private:
    DoubleList< T > stack;
  }
}

template< T >
kovshikov::Stack< T >::Stack(const Stack< T > & s)
{
  stack = s.stack;
}

template< T >
kovshikov::Stack< T >::Stack(Stack< T > && s)
{
  stack = std::move(s.stack); // stack(std::move(s.stack))
}

template< T >
void kovshikov::Stack< T >::push(const Stack< T > val)
{
  stack.pushBack(val);
}

#endif
