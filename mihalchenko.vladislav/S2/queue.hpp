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
  private:
    struct Node
    {
      T data; // вместо конкретного типа, data имеет шаблонный тип T
      Node *next;
      Node(T val, Node *ptr = nullptr) : data(val), next(ptr) {}
    };
    Node *head_;

  public:
    Queue() = default;
    Queue(const Queue &);
    ~Queue() = default;
    Queue &operator=(const Queue &copy);
    // void push(T rhs);
    void push(const T &data); // поместить значение в очередь
    T drop();
    // std::unique_ptr<T> pop();
    T pop(); // извлечь значение из очереди
    void clear();
    T &operator[](const size_t ind);

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
void mihalchenko::Queue<T>::push(const T &data)
{
  Node *newNode = new Node(data, head_);
  head_ = newNode;
  size_++;
}

template <typename T>
// std::unique_ptr<T> mihalchenko::Queue<T>::pop()
T mihalchenko::Queue<T>::pop()
{
  if (head_ == nullptr)
  {
    // throw StackEmptyException();// должен быть определён
  }
  Node *temp = head_;
  T res = head_->data;
  head_ = head_->next;
  delete temp;
  size_--;
  return res;
}

template <typename T>
mihalchenko::Queue<T> &mihalchenko::Queue<T>::operator=(const Queue &copy)
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
T &mihalchenko::Queue<T>::operator[](const size_t index)
{
  size_t c = 0;
  Node *actual = head_;
  while (actual != nullptr)
  {
    if (c == index)
    {
      return actual->data;
    }
    actual = actual->next;
    c++;
  }
  throw std::out_of_range("Index out of range");
}

template <typename T>
template <typename U>
mihalchenko::Queue<T>::ConstIterator<U>::ConstIterator() : node_(nullptr)
{
}

template <typename T>
template <typename U>
mihalchenko::Queue<T>::ConstIterator<U>::ConstIterator(Node *node) : node_(node)
{
}

template <typename T>
template <typename U>
mihalchenko::Queue<T>::ConstIterator<T> &mihalchenko::Queue<T>::ConstIterator<U>::operator++()
{
  node_ = node_->pNext_;
  return *this;
}

template <typename T>
template <typename U>
mihalchenko::Queue<T>::ConstIterator<T> mihalchenko::Queue<T>::ConstIterator<U>::operator++(int)
{
  ConstIterator<T> result(*this);
  ++(*this);
  return result;
}

template <typename T>
template <typename U>
const T &mihalchenko::Queue<T>::ConstIterator<U>::operator*() const
{
  return node_->data_;
}

template <typename T>
template <typename U>
const T *mihalchenko::Queue<T>::ConstIterator<U>::operator->() const
{
  return std::addressof(node_->data_);
}

template <typename T>
template <typename U>
bool mihalchenko::Queue<T>::ConstIterator<U>::operator==(const ConstIterator<T> &rhs) const
{
  return node_ == rhs.node_;
}

template <typename T>
template <typename U>
bool mihalchenko::Queue<T>::ConstIterator<U>::operator!=(const ConstIterator<T> &rhs) const
{
  return !(rhs == *this);
}

template <typename T>
void mihalchenko::Queue<T>::clear()
{
  while (size_)
  {
    pop();
  }
}

#endif