#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace khoroshkin
{
  template< typename T >
  class Queue
  {
  public:
    Queue() = default;
    ~Queue() = default;

    T & front();
    T & back();
    bool empty();
    size_t size();

    void push(const T & value);
    T pop();
  private:
    List< T > queue;
  };
}

template< typename T >
T & khoroshkin::Queue< T >::front()
{
  return queue.front();
}

template< typename T >
T & khoroshkin::Queue< T >::back()
{
  for (auto it = queue.begin(); it != queue.end(); it++)
  {
    if (next(it) == queue.end())
    {
      return *it;
    }
  }
  throw std::logic_error("queue is empty");
}

template< typename T >
bool khoroshkin::Queue< T >::empty()
{
  return queue.isEmpty();
}

template< typename T >
size_t khoroshkin::Queue< T >::size()
{
  return queue.getSize();
}

template< typename T >
void khoroshkin::Queue< T >::push(const T & value)
{
  queue.push_back(value);
}

template< typename T >
T khoroshkin::Queue< T >::pop()
{
  T result = *queue.begin();
  queue.pop_front();
  return result;
}

#endif
