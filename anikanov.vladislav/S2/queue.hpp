#ifndef QUEUE_HPP
#define QUEUE_HPP

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
    List< T > queue;
  };
}

template< typename T >
anikanov::Queue< T >::Queue(const Queue &rhs)
{
  queue = rhs.queue;
}

template< typename T >
anikanov::Queue< T >::Queue(Queue &&rhs) noexcept
{
  queue(std::move(rhs.queue));
}



#endif
