#ifndef STACK_HPP
#define STACK_HPP
#include <stddef.h>
#include <iostream>
#include <string>
#include <memory>
#include <stack>

namespace mihalchenko
{
  // шаблон стека на основе связного списка
  // template class Stack<int>;
  // template <class T>
  template <typename T>
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack &);
    ~Stack() = default;
    Stack &operator=(const Stack &copy);
    void push(const T &data); // поместить значение в стек
    // void push(T rhs);
    // T drop();
    std::unique_ptr<T> pop(); // извлечь значение из стека
  private:
    struct Node
    {
      T data; // вместо конкретного типа, data имеет шаблонный тип T
      Node *next;
      Node(T val, Node *ptr = nullptr) : data(val), next(ptr) {}
    };
    Node *head_;
  };
}

template <typename T>
void mihalchenko::Stack<T>::push(const T &data)
{
  Node *newNode = new Node(data, head_);
  head_ = newNode;
}

template <typename T>
std::unique_ptr<T> mihalchenko::Stack<T>::pop()
{
  if (head_ == nullptr)
  {
    // throw StackEmptyException();// должен быть определён
    // https://stackoverflow.com/questions/40073460/exception-handling-in-a-class-c
  }
  Node *temp = head_;
  std::unique_ptr<T> res(new T(std::move(head_->data)));
  head_ = head_->next;
  delete temp;
  return res;
}

template <typename T>
mihalchenko::Stack<T> &mihalchenko::Stack<T>::operator=(const Stack &copy)
{
  /*  if (this == &copy)
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
    }*/
  return *this;
}

#endif
