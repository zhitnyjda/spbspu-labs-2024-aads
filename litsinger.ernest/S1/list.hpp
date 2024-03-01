#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "Iterator.hpp"
#include "node.hpp"

namespace litsinger
{
  template< typename T >
  class List
  {
  public:
    List();
    void pushBack(T value);
    void pushFront(T value);
    size_t getSize();
    void popFront();
    void popBack();
  private:
    head(nullptr);
    tail(nullptr);
    size_t size = 0;
  };
}
template <typename T>
void pushFront(T data)
{
  Node< T > * ptr = new Node< T >(data);
  head = ptr->next;
  if (head != nullptr)
  {
    head->next = ptr;
  }
  if (head == nullptr)
  {
    head = ptr;
  }
  head = ptr;
}
template <typename T>
void pushBack(T data)
{
  Node< T > * ptr = new Node< T >(data);
  ptr->prev = tail;
  if (tail != nullptr)
  {
    tail->prev = ptr;
  }
  if (head == nullptr)
  {
    head = ptr;
  }
  tail = ptr;
}
template <typename T>
void pop_front()
{
  if (head == nullptr)
  {
    return;
  }
 Node<T> * ptr = head->next;
  if (ptr != nullptr)
  {
    ptr->prev = nullptr;
  }
  delete head;
  head = ptr;
}
template <typename T>
void pop_back()
{
  if (head == nullptr)
  {
    return;
  }
 Node<T> * ptr = tail->prev;
  if (ptr != nullptr)
  {
    ptr->prev = nullptr;
  }
  delete head;
  head = ptr;
}
#endif