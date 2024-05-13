#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

namespace mihalchenko
{
  template < typename T >
  class Stack
  {
  public:
    Stack() = default;
    ~Stack() = default;
    Stack(const Stack< T > &copy);
    void push(const T &data);
    T pop();
    T watch(size_t index);
    void clear();
    size_t getSize();
    void setSize(const size_t size);

  private:
    List< T > containStack;
  };
}

template < typename T >
mihalchenko::Stack< T >::Stack(const Stack< T > &copy)
{
  containStack(copy);
}

template < typename T >
void mihalchenko::Stack< T >::push(const T &data)
{
  containStack.push_front(data);
}

template < typename T >
T mihalchenko::Stack< T >::pop()
{
  T res = containStack.getT();
  containStack.pop_front();
  return res;
}

template < typename T >
T mihalchenko::Stack< T >::watch(size_t index)
{
  T res = containStack.watch(index);
  return res;
}

template < typename T >
void mihalchenko::Stack< T >::clear()
{
  containStack.clear();
}

template < typename T >
size_t mihalchenko::Stack< T >::getSize()
{
  return containStack.getSize();
}

template < typename T >
void mihalchenko::Stack< T >::setSize(const size_t size)
{
  containStack.setSize(size);
}

#endif
