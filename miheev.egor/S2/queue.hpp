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
    ~Queue();

    bool empty() const;
    size_t size() const;
    T& front();
    T& back()
    void push(const T&)

    void pop();
    void emplace();
    void swap(); // TODO: change to correct signature

  private:

  }
}
#endif
