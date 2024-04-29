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

    bool empty() const;
    size_t size() const;
    T& front();
    T& back();
    void push(const T&);
    T drop();
    void pop();
    void emplace();
    void swap(Queue&) noexcept;

    void print();
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
  container_ = rhs;
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
  container_.pushFront(value);
}

template< typename T >
void miheev::Queue< T >::print()
{
  container_.print();
}

#endif
