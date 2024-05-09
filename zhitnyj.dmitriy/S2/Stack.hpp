#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "List.hpp"

template< typename T >
class Stack
{
public:
    Stack() = default;
    ~Stack() = default;

    bool empty() const;
    size_t size() const;
    void push(T value);
    void push_back(T value);
    void pop();

    T& top();
    T& back();

private:
    List<T> list;
};

template< typename T >
void Stack<T>::push(T value)
{
  list.push_front(value);
}

template< typename T >
void Stack<T>::push_back(T value)
{
  list.push_back(value);
}

template< typename T >
void Stack<T>::pop()
{
  if (list.empty())
  {
    throw std::out_of_range("Stack is empty");
  }
  list.pop();
}

template< typename T >
T& Stack<T>::top()
{
  if (list.empty())
  {
    throw std::out_of_range("Stack is empty");
  }
  return list[0];
}

template< typename T >
T& Stack<T>::back()
{
  if (list.empty())
  {
    throw std::out_of_range("Stack is empty");
  }
  return list[list.size() - 1];
}

template< typename T >
bool Stack<T>::empty() const
{
  return list.empty();
}

template< typename T >
size_t Stack<T>::size() const
{
  return list.size();
}

#endif
