#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace khoroshkin
{
  template< typename T >
  class Stack
  {
  public:
    Stack() = default;
    ~Stack() = default;

    T & top();
    bool empty();
    size_t size();
    
    void push(const T & value);
    T pop();
  private:
    List< T > stack;
  };
}

template< typename T >
T & khoroshkin::Stack< T >::top()
{
  for (auto it = stack.begin(); it != stack.end(); it++)
  {
    if (next(it) == stack.end())
    {
      return *it;
    }
  }
  throw std::logic_error("stack is empty");
}

template< typename T >
bool khoroshkin::Stack< T >::empty()
{
  return stack.isEmpty();
}

template< typename T >
size_t khoroshkin::Stack< T >::size()
{
  return stack.getSize();
}

template< typename T >
void khoroshkin::Stack< T >::push(const T & value)
{
  stack.push_back(value);
}

template< typename T >
T khoroshkin::Stack< T >::pop()
{
  T result;
  auto it_before = stack.begin();
  for (auto it = stack.begin(); it != stack.end(); it++)
  {
    if (next(it) == stack.end())
    {
      result = *it;
      stack.erase_after(it_before);
    }
    it_before = it;
  }
  return result;
}

#endif
