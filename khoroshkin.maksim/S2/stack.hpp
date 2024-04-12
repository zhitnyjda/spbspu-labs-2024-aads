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
    Stack(const Stack & rhs);
    Stack(Stack && rhs);

    T & top() const noexcept;
    bool isEmpty();
    size_t getSize();

    void push(const T & value);
    T pop();
  private:
    List< T > stack;
  };
}

template< typename T >
khoroshkin::Stack< T >::Stack(const Stack & rhs)
{
  stack = rhs.stack;
}

template< typename T >
khoroshkin::Stack< T >::Stack(Stack && rhs)
{
  stack(std::move(rhs.stack));
}

template< typename T >
T & khoroshkin::Stack< T >::top() const noexcept
{
  for (auto it = stack.begin(); it != stack.end(); it++)
  {
    if (next(it) == stack.end())
    {
      return *it;
    }
  }
  return *stack.begin();
}

template< typename T >
bool khoroshkin::Stack< T >::isEmpty()
{
  return stack.isEmpty();
}

template< typename T >
size_t khoroshkin::Stack< T >::getSize()
{
  return stack.getSize();
}

template< typename T >
void khoroshkin::Stack< T >::push(const T & value)
{
  try
  {
    stack.push_back(value);
  }
  catch(const std::bad_alloc & e)
  {
    throw e;
  }
}

template< typename T >
T khoroshkin::Stack< T >::pop()
{
  if (stack.isEmpty())
  {
    throw std::logic_error("stack is empty");
  }
  auto it_before = stack.begin();
  auto it = stack.begin();
  while (it != stack.end())
  {
    if (next(it) == stack.end())
    {
      break;
    }
    it_before = it;
    ++it;
  }
  T result = *it;
  stack.erase_after(it_before);

  return result;
}

#endif
