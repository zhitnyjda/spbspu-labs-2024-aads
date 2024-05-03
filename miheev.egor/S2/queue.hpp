#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"

namespace miheev
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const T& value);
    Queue(const Queue& rhs);
    ~Queue() = default;

    Queue& operator=(const Queue& rhs);

    bool empty() const;
    size_t size() const;
    T& front();
    T& back();
    void push(const T&);
    void pop();
    T drop();
    template< class... Args >
    void emplace(Args&&... args);
    void swap(Queue&) noexcept;

    void print() const;
  private:
    List< T > container_;
  };
}

template< typename T >
miheev::Queue< T >::Queue():
  container_(List< T >())
{}

template< typename T >
miheev::Queue< T >::Queue(const T& value):
  container_(List< T >(value))
{}

template< typename T >
miheev::Queue< T >::Queue(const Queue< T >& rhs)
{
  container_ = rhs.container_;
}

template< typename T >
miheev::Queue< T >& miheev::Queue< T >::operator=(const miheev::Queue< T >& rhs)
{
  container_ = rhs.container_;
  return *this;
}

template< typename T >
bool miheev::Queue< T >::empty() const
{
  return container_.empty();
}

template< typename T >
size_t miheev::Queue< T >::size() const
{
  return container_.size();
}

template< typename T >
T& miheev::Queue< T >::front()
{
  return container_.front();
}

template< typename T >
T& miheev::Queue< T >::back()
{
  typename List< T >::Iterator iter(container_.begin());
  for (size_t i = 1; i < container_.size(); i++)
  {
    iter++;
  }
  return *iter;
}

template< typename T >
void miheev::Queue< T > ::push(const T& value)
{
  container_.pushBack(value);
}

template< typename T >
void miheev::Queue< T >::pop()
{
  container_.popFront();
}

template< typename T >
T miheev::Queue< T >::drop()
{
  T value = back();
  pop();
  return value;
}

template< typename T >
template< class... Args >
void miheev::Queue< T >::emplace(Args&&... args)
{
  push(std::forward< Args > (args)...);
}

template< typename T >
void miheev::Queue< T >::swap(Queue& rhs) noexcept
{
  container_.swap(rhs);
}

template< typename T >
void miheev::Queue< T >::print() const
{
  container_.print();
}

#endif
