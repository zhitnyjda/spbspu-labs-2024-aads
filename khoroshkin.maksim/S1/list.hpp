#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"
#include <cstddef>
#include <stdexcept>

namespace khoroshkin
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List();
    List(const List & obj);

    void push_back(T data);
    void pop_front();
    void clear();
    size_t getSize();
    bool isEmpty();
    T & operator[](const size_t index);
    ListIterator< T > begin();
    ListIterator< T > end();

    ListIterator< T > next(ListIterator< T > it);
  private:
    size_t size;
    Node< T > * head;
  };
}

template< typename T >
khoroshkin::List< T >::List() :
  size(0), head(nullptr)
{}

template < typename T >
khoroshkin::List< T >::List(const khoroshkin::List< T > & obj)
{
  if (obj.head == nullptr)
  {
    head = nullptr;
  }
  else
  {
    head = new Node< T >(*obj.head);
  }
  size = obj.size;
}

template< typename T >
void khoroshkin::List< T >::push_back(T data)
{
  if (head == nullptr)
  {
      head = new Node< T >(data);
  }
  else
  {
    Node< T > * current = this->head;
    while (current->pNext != nullptr)
    {
      current = current->pNext;
    }
    current->pNext = new Node< T >(data);
  }
  size++;
}

template < typename T >
khoroshkin::ListIterator< T > khoroshkin::List< T >::next(khoroshkin::ListIterator< T > it)
{
  return ++it;
}

template< typename T >
T & khoroshkin::List< T >::operator[](const size_t index)
{
  size_t counter = 0;
  Node< T > * current = this->head;
  while (current != nullptr)
  {
    if (counter == index)
    {
      return current->data;
    }
    current = current->pNext;
    counter++;
  }
  throw std::out_of_range("Index out of range");
}

template < typename T >
void khoroshkin::List< T >::pop_front()
{
  Node< T > * temp = head;
  head = head->pNext;
  delete temp;
  size--;
}

template < typename T >
void khoroshkin::List< T >::clear()
{
  while (size)
  {
    pop_front();
  }
}

template < typename T >
size_t khoroshkin::List< T >::getSize()
{
  return size;
}

template < typename T >
bool khoroshkin::List< T >::isEmpty()
{
  return !head;
}

template < typename T >
khoroshkin::List< T >::~List()
{
  clear();
}

template < typename T >
khoroshkin::ListIterator< T > khoroshkin::List< T >::begin()
{
  return this->head;
}

template < typename T >
khoroshkin::ListIterator< T > khoroshkin::List< T >::end()
{
  Node< T > * subhead = head;
  while (subhead)
  {
    subhead = subhead->pNext;
  }
  return subhead;
}

#endif
