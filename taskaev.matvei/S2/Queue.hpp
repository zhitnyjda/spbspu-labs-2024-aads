#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "List.hpp"

namespace taskaev
{
  template < typename T >
  class Queue
  {
  public:
    Queue() = default;
    ~Queue() = default;
    void push(const T& value);
    void pop();
    bool isEmpty() const noexcept;
    T& front();
  private:
    List< T > greenfield;
  };
}

template < typename T >
void taskaev::Queue< T >::push(const T& value)
{
  greenfield.pushBack(value);
}

template < typename T >
void taskaev::Queue< T >::pop()
{
  greenfield.popFront();
}

template < typename T >
bool taskaev::Queue< T >::isEmpty() const noexcept
{
  return greenfield.isEmpty();
}

template < typename T >
T& taskaev::Queue< T >::front()
{
  return storage.front();
}

#endif
