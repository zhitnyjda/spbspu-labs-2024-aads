#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"
#include <cstddef>
#include <stdexcept>
#include <initializer_list>

namespace khoroshkin
{
  template< typename T >
  class List
  {
  public:
    List();
    List(size_t count, const T & value);
    List(std::initializer_list< T > init);
    ~List();
    List(const List & obj);
    List< T > & operator=(const List & obj);
    List(List && obj);
    List< T > & operator=(List && obj);

    void assign(size_t count, const T & value);
    void assign(ListIterator< T > first, ListIterator< T > last);
    void assign(std::initializer_list< T > ilist);

    void push_back(T data);
    void pop_front();
    Node< T > * front();
    void clear();
    int getSize();
    bool isEmpty();
    T & operator[](const size_t index);
    void swap(List< T > & other);
    void remove(const T & value);
    template< typename UnaryPredicate >
    void remove_if(UnaryPredicate p);

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

template< typename T >
khoroshkin::List< T >::List(size_t count, const T & value)
{
  for (size_t i = 0; i < count; ++i)
  {
    this->push_back(value);
  }
}

template< typename T >
khoroshkin::List< T >::List(std::initializer_list< T > init)
{
  for (auto it = init.begin(); it != init.end(); ++it)
  {
    this->push_back(*it);
  }
}

template< typename T >
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

template< typename T >
khoroshkin::List< T >::List(khoroshkin::List< T > && obj) :
  size(obj.size), head(obj.head)
{
  obj.size = 0;
  obj.head = nullptr;
}

template< typename T >
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
void khoroshkin::List< T >::assign(size_t count, const T & value)
{
  this->clear();
  for (size_t i = 0; i < count; ++i)
  {
    this->push_back(value);
  }
}

template< typename T >
void khoroshkin::List< T >::assign(khoroshkin::ListIterator< T > first, khoroshkin::ListIterator< T > last)
{
  this->clear();
  while (first != last)
  {
    this->push_back(*first);
    first++;
  }
}

template< typename T >
void khoroshkin::List< T >::assign(std::initializer_list< T > ilist)
{
  this->clear();
  for (auto it = ilist.begin(); it != ilist.end(); ++it)
  {
    this->push_back(*it);
  }
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

template< typename T >
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

template< typename T >
void khoroshkin::List< T >::pop_front()
{
  Node< T > * temp = head;
  head = head->pNext;
  delete temp;
  size--;
}

template< typename T >
khoroshkin::Node< T > * khoroshkin::List< T >::front()
{
  return head;
}

template< typename T >
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

template< typename T >
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


template< typename T >
khoroshkin::ListIterator< T > khoroshkin::List< T >::begin()
{
  if (isEmpty())
  {
    return end();
  }
  return this->head;
}

template< typename T >
khoroshkin::ListIterator< T > khoroshkin::List< T >::end()
{
  return nullptr;
}

template< typename T >
void khoroshkin::List< T >::remove(const T & value)
{
  for (auto it = this->begin(); it != this->end(); ++it)
  {
    if (*it == value && *it == *this->begin())
    {
      this->pop_front();
      it = this->begin();
    }
    else if (next(it) != this->end() && *next(it) == value)
    {
      Node< T > * subhead = it.node;
      Node< T > * todelete = subhead->pNext;
      subhead->pNext = todelete->pNext;
      delete todelete;
      this->size--;
      it = this->begin();
    }
  }
}

template< typename T >
template< typename UnaryPredicate >
void khoroshkin::List< T >::remove_if(UnaryPredicate p)
{
  for (auto it = this->begin(); it != this->end(); ++it)
  {
    if (p(*it) && *it == *this->begin())
    {
      this->pop_front();
      it = this->begin();
    }
    else if (next(it) != this->end() && p(*next(it)))
    {
      Node< T > * subhead = it.node;
      Node< T > * todelete = subhead->pNext;
      subhead->pNext = todelete->pNext;
      delete todelete;
      this->size--;
      it = this->begin();
    }
  }
}

#endif
