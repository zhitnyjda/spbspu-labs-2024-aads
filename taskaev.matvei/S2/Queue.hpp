#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "List.hpp"

namespace taskaev
{
  template < typename T >
  class Queue
  {
  public:
    Queue();
    ~Queue() = default;
    void push(const T& value);
    void pop();
    bool isEmpty() const noexcept;
    T& front();
  private:
    List< T > container;
  };
}

template< typename T >
taskaev::Queue< T >::Queue():
  container(List< T >())
{}

template < typename T >
void taskaev::Queue< T >::push(const T& value)
{
  container.pushBack(value);
}

template < typename T >
void taskaev::Queue< T >::pop()
{
  container.popFront();
}

template < typename T >
bool taskaev::Queue< T >::isEmpty() const noexcept
{
  return container.isEmpty();
}

template < typename T >
T& taskaev::Queue< T >::front()
{
  return container.front();
}

#endif
