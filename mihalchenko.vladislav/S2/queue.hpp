#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"
// #include <iostream>
// #include <string>
// #include <memory>
#include <queue>
// #include <algorithm>

namespace mihalchenko
{
  template <typename T>
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue<T> &copy);
    ~Queue() = default;
    // Queue & operator=(const Queue &copy);
    void push(const T &data); // поместить значение в очередь
    // T drop();
    T pop(); // извлечь значение из очереди
    T watch(size_t index);
    void clear();
    size_t getSize();
    // T &operator[](const size_t ind);
    size_t size_;

  private:
    List<T> containQueue;
  };
}

template <typename T>
mihalchenko::Queue<T>::Queue(const Queue<T> &copy)
{
  containQueue(copy);
}

template <typename T>
void mihalchenko::Queue<T>::push(const T &data)
{
  containQueue.push_back(data);
}

template <typename T>
T mihalchenko::Queue<T>::pop()
{
  T res = containQueue.pop_front();
  return res;
}

template <typename T>
T mihalchenko::Queue<T>::watch(size_t index)
{
  T res = containQueue.watch(index);
  return res;
}

/*template <typename T>
mihalchenko::Queue<T> &mihalchenko::Queue<T>::operator=(const Queue &copy)
{
  if (this == &copy)
  {
    return *this;
  }
  clear();
  size_ = copy.size_;
  Node *pointer = copy.head_;
  while (pointer)
  {
    push(pointer->data);
    pointer = pointer->next;
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
 */

template <typename T>
void mihalchenko::Queue<T>::clear()
{
  containQueue.clear();
}

template <typename T>
size_t mihalchenko::Queue<T>::getSize()
{
  return containQueue.getSize();
}

#endif
