#ifndef STACK_HPP
#define STACK_HPP
#include <stddef.h>
#include <iostream>
#include <string>
#include <memory>
#include <stack>
// #include <cstdlib>
#include <unistd.h>

namespace mihalchenko
{
  // шаблон стека на основе связного списка
  // template class Stack<int>;
  template <typename T>
  class Stack
  {
  private:
    struct Node
    {
      T data; // вместо конкретного типа, data имеет шаблонный тип T
      Node *next;
      Node(T val, Node *ptr = nullptr) : data(val), next(ptr) {}
    };
    Node *head_;

  public:
    Stack() = default;
    Stack(const Stack &);
    ~Stack() = default;
    Stack &operator=(const Stack &copy);
    void push(const T &data); // поместить значение в стек
    // 12 void push(T rhs);
    // T drop();
    T pop(); // извлечь значение из стека
    // std::unique_ptr<T> pop();
    void clear();

    template <typename U>
    class ConstIterator : public std::iterator<std::forward_iterator_tag, T>
    {
    public:
      //  friend class List<T>;
      ConstIterator();
      ConstIterator(Node *ind);
      ConstIterator(const ConstIterator &) = default;

      ~ConstIterator() = default;

      ConstIterator<T> &operator++();
      ConstIterator<T> operator++(int);
      const T &operator*() const;
      const T *operator->() const;
      bool operator!=(const ConstIterator<T> &rhs) const;
      bool operator==(const ConstIterator<T> &rhs) const;

    private:
      Node *node_;
    };

    // Node *begin_;
    size_t size_;
  };
}

template <typename T>
void mihalchenko::Stack<T>::push(const T &data)
{
  Node *newNode = new Node(data, head_);
  head_ = newNode;
  size_++;
}

template <typename T>
// std::unique_ptr<T> mihalchenko::Stack<T>::pop()
T mihalchenko::Stack<T>::pop()
{
  if (head_ == nullptr)
  {
    // throw StackEmptyException();// должен быть определён
    // https://stackoverflow.com/questions/40073460/exception-handling-in-a-class-c
    std::cout << "laga" << std::endl;
    // std::cout << "error dinamic " << std::endl;
    return 0;
  }
  Node *temp = head_;
  // std::unique_ptr<T> res(new T(std::move(head_->data)));
  T res = head_->data;
  head_ = head_->next;
  delete temp;
  size_--;
  return res;
}

template <typename T>
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

template <typename T>
template <typename U>
mihalchenko::Stack<T>::ConstIterator<U>::ConstIterator() : node_(nullptr)
{
}

template <typename T>
template <typename U>
mihalchenko::Stack<T>::ConstIterator<U>::ConstIterator(Node *node) : node_(node)
{
}

template <typename T>
template <typename U>
mihalchenko::Stack<T>::ConstIterator<T> &mihalchenko::Stack<T>::ConstIterator<U>::operator++()
{
  node_ = node_->pNext_;
  return *this;
}

template <typename T>
template <typename U>
mihalchenko::Stack<T>::ConstIterator<T> mihalchenko::Stack<T>::ConstIterator<U>::operator++(int)
{
  ConstIterator<T> result(*this);
  ++(*this);
  return result;
}

template <typename T>
template <typename U>
const T &mihalchenko::Stack<T>::ConstIterator<U>::operator*() const
{
  return node_->data_;
}

template <typename T>
template <typename U>
const T *mihalchenko::Stack<T>::ConstIterator<U>::operator->() const
{
  return std::addressof(node_->data_);
}

template <typename T>
template <typename U>
bool mihalchenko::Stack<T>::ConstIterator<U>::operator==(const ConstIterator<T> &rhs) const
{
  return node_ == rhs.node_;
}

template <typename T>
template <typename U>
bool mihalchenko::Stack<T>::ConstIterator<U>::operator!=(const ConstIterator<T> &rhs) const
{
  return !(rhs == *this);
}

template <typename T>
void mihalchenko::Stack<T>::clear()
{
  while (size_ > 0)
  {
    pop();
  }
}

#endif
