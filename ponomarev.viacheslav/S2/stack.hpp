#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

namespace ponomarev
{
  template < typename T >
  class Stack {
  public:
    Stack();
    explicit Stack(const List< T > & data);
    Stack(const Stack< T > & other);
    Stack(Stack< T > && other);
    ~Stack() = default;

    Stack & operator=(const Stack & other);
    Stack & operator=(Stack && other);

    T & getUp() const;

    bool empty() const;
    size_t size() const;

    void push(const T & value);
    void push(T && value);
    void pop();

  private:
    List< T > container_;
  };
}

template < typename T >
ponomarev::Stack < T >::Stack():
  container_(List< T >())
{}

template < typename T >
ponomarev::Stack< T >::Stack(const List< T > & data):
  container_(data)
{}

template < typename T >
ponomarev::Stack< T >::Stack(const Stack & other):
  container_(other.container_)
{}

template < typename T >
ponomarev::Stack< T >::Stack(Stack && other):
  container_(std::move(other.container_))
{}

template < typename T >
ponomarev::Stack< T > & ponomarev::Stack< T >::operator=(const Stack & other)
{
  container_ = other.container_;
}

template < typename T >
ponomarev::Stack< T > & ponomarev::Stack< T >::operator=(Stack && other)
{
  container_ = std::move(other.container_);
}

template < typename T >
T & ponomarev::Stack< T >::getUp() const
{
  return container_->head->data;
}

template < typename T >
bool ponomarev::Stack< T >::empty() const
{
  return container_.isEmpty();
}

template < typename T >
size_t ponomarev::Stack< T >::size() const
{
  return container_.getSize();
}

template < typename T >
void ponomarev::Stack< T >::push(const T & value)
{
  container_.pushFront(value);
}

template < typename T >
void ponomarev::Stack< T >::push(T && value)
{
  container_.pushFront(value);
}

template < typename T >
void ponomarev::Stack< T >::pop()
{
  container_.popFront();
}

#endif
