#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cassert>
#include "../common/list.hpp"

namespace anikanov {

  template< typename T >
  class Queue {
  public:
    Queue() = default;
    ~Queue() = default;
    Queue(const Queue &rhs);
    Queue(Queue &&rhs) noexcept;

    T &front() noexcept;
    const T &front() const noexcept;
    T &back() noexcept;
    const T &back() const noexcept;

    bool isEmpty() const;
    size_t getSize() const;

    void push(const T &value);
    void pop();
  private:
    List< T > list;
  };
}

template< typename T >
anikanov::Queue< T >::Queue(const Queue &rhs)
{
  list = rhs.queue;
}

template< typename T >
anikanov::Queue< T >::Queue(Queue &&rhs) noexcept
{
  list(std::move(rhs.queue));
}

template< typename T >
T &anikanov::Queue< T >::front() noexcept
{
  assert(!list.empty());
  return list[0];
}

template< typename T >
const T &anikanov::Queue< T >::front() const noexcept
{
  assert(!list.empty());
  return list[0];
}

template< typename T >
T &anikanov::Queue< T >::back() noexcept
{
  assert(!list.empty());
  return list[list.size() - 1];
}

template< typename T >
const T &anikanov::Queue< T >::back() const noexcept
{
  assert(!list.empty());
  return list[list.size() - 1];
}

template< typename T >
bool anikanov::Queue< T >::isEmpty() const
{
  return list.empty();
}

template< typename T >
size_t anikanov::Queue< T >::getSize() const
{
  return list.size();
}

template< typename T >
void anikanov::Queue< T >::push(const T &value)
{
  list.push_back(value);
}

template< typename T >
void anikanov::Queue< T >::pop()
{
  assert(!list.empty());
  list.pop(0);
}

#endif
