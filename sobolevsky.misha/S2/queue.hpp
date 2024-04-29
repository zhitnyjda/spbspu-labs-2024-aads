#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>

namespace sobolevsky
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue& rhs) noexcept;
    Queue(Queue&& rhs);
    ~Queue() = default;

    void push(T data);
    T back();
    void pop();
    bool empty();
    size_t size();
  private:
    class Node
    {
      friend class Queue< T >;
      T data;
      Node *prev;
      Node(T data)
      {
        this->data = data;
        prev = nullptr;
      }
    };

    Node *last;
    Node *first;
    size_t size_;
  };
}

template< typename T >
sobolevsky::Queue< T >::Queue()
{
  last = nullptr;
  first = nullptr;
  size_ = 0;
}

template< typename T >
sobolevsky::Queue< T >::Queue(const Queue& rhs) noexcept
{
  last = rhs.last;
  first = rhs.first;
  size_ = rhs.size_;
}

template< typename T >
sobolevsky::Queue< T >::Queue(Queue&& rhs)
{
  last(std::move(rhs.last));
  first(std::move(rhs.first));
  size_ = rhs.size_;
}

template< typename T >
void sobolevsky::Queue< T >::push(T data)
{
  if (size_ == 0)
  {
    Node *ptr = new Node(data);
    ptr->prev = nullptr;
    first = ptr;
    last = ptr;
  }
  else
  {
    Node *ptr = new Node(data);
    ptr->prev = nullptr;
    last->prev = ptr;
    last = ptr;
  }
  size_++;
}

template< typename T >
T sobolevsky::Queue< T >::back()
{
  if (first == nullptr)
  {
    throw std::logic_error("Queue is empty");
  }
  return first->data;
}

template< typename T >
void sobolevsky::Queue< T >::pop()
{
  Node *tempNode = first;
  first = first->prev;
  size_--;
  delete tempNode;
}

template< typename T >
bool sobolevsky::Queue< T >::empty()
{
  return (size_ == 0);
}

template< typename T >
size_t sobolevsky::Queue< T >::size()
{
  return size_;
}

#endif
