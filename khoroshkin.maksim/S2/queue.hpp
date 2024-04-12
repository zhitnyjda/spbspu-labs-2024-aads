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
    Queue(const Queue & rhs);
    Queue(Queue && rhs);

    T & front() const noexcept;
    T & back() const noexcept;
    bool isEmpty();
    size_t getSize();

    void push(const T & value);
    T pop();
  private:
    List< T > queue;
  };
}

template< typename T >
khoroshkin::Queue< T >::Queue(const Queue & rhs)
{
  queue = rhs.queue;
}

template< typename T >
khoroshkin::Queue< T >::Queue(Queue && rhs)
{
  queue(std::move(rhs.queue));
}

template< typename T >
T & khoroshkin::Queue< T >::front() const noexcept
{
  return queue.front();
}

template< typename T >
T & khoroshkin::Queue< T >::back() const noexcept
{
  for (auto it = queue.begin(); it != queue.end(); it++)
  {
    if (next(it) == queue.end())
    {
      return *it;
    }
  }
  return *queue.begin();
}

template< typename T >
bool khoroshkin::Queue< T >::isEmpty()
{
  return queue.isEmpty();
}

template< typename T >
size_t khoroshkin::Queue< T >::getSize()
{
  return queue.getSize();
}

template< typename T >
void khoroshkin::Queue< T >::push(const T & value)
{
  try
  {
    queue.push_back(value);
  }
  catch(const std::bad_alloc & e)
  {
    queue.clear();
    throw e;
  }
}

template< typename T >
T khoroshkin::Queue< T >::pop()
{
  T result = *queue.begin();
  queue.pop_front();
  return result;
}

#endif
