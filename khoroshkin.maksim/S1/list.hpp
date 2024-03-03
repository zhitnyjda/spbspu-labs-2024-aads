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
    List< T > & operator=(const List & obj);
    List(List && obj);
    List< T > & operator=(List && obj);

    void push_back(T data);
    void pop_front();
    Node< T > * front();
    void clear();
    int getSize();
    bool isEmpty();
    T & operator[](const size_t index);
    void swap(List< T > & other);

    ListIterator< T > begin();
    ListIterator< T > end();

    ListIterator< T > next(ListIterator< T > it);
  private:
    int size;
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

template < typename T >
khoroshkin::List< T > & khoroshkin::List< T >::operator=(const List & obj)
{
  if (this != &obj)
  {
    this->size = obj.size;
    clear();
    Node< T > * temp = obj.head;
    while (temp)
    {
      push_back(temp->data);
      temp = temp->pNext;
    }
  }
  return *this;
}

template < typename T >
khoroshkin::List< T >::List(khoroshkin::List< T > && obj) :
  size(obj.size), head(obj.head)
{
  obj.size = 0;
  obj.head = nullptr;
}

template < typename T >
khoroshkin::List< T > & khoroshkin::List< T >::operator=(List && obj)
{
  if (this != &obj)
  {
    clear();
    this->size = obj.size;
    while (obj.head)
    {
      push_back(obj.head->data);
      obj.head = obj.head->pNext;
    }
  }
  obj.clear();
  return *this;
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
khoroshkin::Node< T > * khoroshkin::List< T >::front()
{
  return head;
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
int khoroshkin::List< T >::getSize()
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

template< typename T >
void khoroshkin::List< T >::swap(khoroshkin::List< T > & other)
{
  Node < T > * tempH = this->head;
  this->head = other.head;
  other.head = tempH;

  int tempS = this->size;
  this->size = other.size;
  other.size = tempS;
}


template < typename T >
khoroshkin::ListIterator< T > khoroshkin::List< T >::begin()
{
  if (isEmpty())
  {
    return end();
  }
  return this->head;
}

template < typename T >
khoroshkin::ListIterator< T > khoroshkin::List< T >::end()
{
  return nullptr;
}

#endif
