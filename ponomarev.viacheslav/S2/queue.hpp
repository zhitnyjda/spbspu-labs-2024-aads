#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"

namespace ponomarev
{
  template < typename T >
  class Queue {
  public:
    Queue();
    Queue(const T & value);
    Queue(const Queue & rhs);
    ~Queue() = default;

    Queue< T > & operator=(const Queue & other);
    Queue< T > & operator=(Queue && other);

    bool empty() const;
    size_t size() const;

    void push(const T & value);
    void push(T && value);
    void pop();

  private:
    List< T > container_;
  };
}

template< typename T >
ponomarev::Queue< T >::Queue():
  container_(List< T >())
{}

template< typename T >
ponomarev::Queue< T >::Queue(const T & value):
  container_(List< T >(value))
{}

template< typename T >
ponomarev::Queue< T >::Queue(const Queue< T > & rhs)
{
  container_ = rhs.container_;
}

ponomarev::Queue< T >& ponomarev::Queue< T >::operator=(const Queue & other)
{
  container_ = other.container_;
}

template < typename T >
ponomarev::Queue< T > & ponomarev::Queue< T >::operator=(Queue && other)
{
  container_ = std::move(other.container_);
}

template < typename T >
bool ponomarev::Queue< T >::empty() const
{
  return container_.isEmpty();
}

template < typename T >
size_t ponomarev::Queue< T >::size() const
{
  container_.getSize();
}

template < typename T >
void ponomarev::Queue< T >::push(const T & value)
{
  container_.pushBack(value);
}

template < typename T >
void ponomarev::Queue< T >::push(T && value)
{
  container_.pushBack(std::move(value));
}

template < typename T >
void ponomarev::Queue< T >::pop()
{
  container_.popFront();
}

#endif
