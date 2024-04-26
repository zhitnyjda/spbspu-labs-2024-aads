#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
#include <string>
#include <memory>
#include <queue>

namespace mihalchenko
{
  template <typename T>
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue &);
    ~Queue() = default;
    Queue &operator=(const Queue &copy);
    // void push(T rhs);
    void push(const T &data); // поместить значение в стек
    T drop();
    std::unique_ptr<T> pop();

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
void mihalchenko::Queue<T>::push(const T &data)
{
  Node *newNode = new Node(data, head_);
  head_ = newNode;
}

template <typename T>
std::unique_ptr<T> mihalchenko::Queue<T>::pop()
{
  if (head_ == nullptr)
  {
    // throw StackEmptyException();// должен быть определён
  }
  Node *temp = head_;
  T res = head_->data;
  head_ = head_->next;
  delete temp;
  return res;
}

template <typename T>
mihalchenko::Queue<T> &mihalchenko::Queue<T>::operator=(const Queue &copy)
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

  // queue = rhs.queue;
  return *this;
}

#endif
