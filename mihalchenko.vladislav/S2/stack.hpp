#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"
// #include <stddef.h>
// #include <unistd.h>
// #include <iostream>
// #include <string>
// #include <memory>
#include <stack>

namespace mihalchenko
{
  // шаблон стека на основе связного списка
  template <typename T>
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack<T> &copy);
    ~Stack() = default;
    // Stack & operator=(const Stack & copy);
    void push(const T &data); // поместить значение в стек
    T pop();                  // извлечь значение из стека
    void clear();
    size_t getSize();
    size_t size_;

  private:
    List<T> containStack;
  };
}

template <typename T>
mihalchenko::Stack<T>::Stack(const Stack<T> &copy)
{
  containStack(copy);
}

template <typename T>
void mihalchenko::Stack<T>::push(const T &data)
{
  containStack.push_front(data);
}

template <typename T>
T mihalchenko::Stack<T>::pop()
{
  T res = containStack.pop_front();
  return res;
}

/*template <typename T>
mihalchenko::Stack<T> &mihalchenko::Stack<T>::operator=(const Stack &copy)
{
  if (this == &copy)
  {
    return *this;
  }
  size_ = copy.size_;
  clear();
  Node *pointer = copy.begin_;
  while (pointer)
  {
    push_back(pointer->data_);
    pointer = pointer->pNext_;
  }
  return *this;
}
*/

template <typename T>
void mihalchenko::Stack<T>::clear()
{
  containStack.clear();
}

template <typename T>
size_t mihalchenko::Stack<T>::getSize()
{
  return containStack.getSize();
}

#endif
