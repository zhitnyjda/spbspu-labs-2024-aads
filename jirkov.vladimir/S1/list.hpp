#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <iostream>
#include "iterator.hpp"
#include "node.hpp"

namespace jirkov
{
  template < typename T >
  class List
  {
  public:
    List();
    List(size_t n, const T& value);
    List(const List<T>& otherList);
    List(List<T>&& otherList);
    ~List();
    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    bool empty();
    void clear();
    void swap(List<T>& otherList);
    void assign(size_t n, const T& value);
    size_t getSize();
    Node<T>* operator[](const int index);
    Iterator<T> begin() const;
    Iterator<T> end() const;
    const Iterator<T> cbegin() const;
    const Iterator<T> cend() const;
    Node< T >* head_;
    Node< T >* tail_;
  };
}

template< typename T >
jirkov::List< T >::List() :
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
jirkov::List< T >::List(size_t n, const T& value)
{
  head_ = nullptr;
  tail_ = nullptr;
  for (size_t i = 0; i < n; i++)
  {
    pushBack(value);
  }
}

template< typename T >
jirkov::List< T >::List(const List< T >& otherList)
{
  head_ = nullptr;
  tail_ = nullptr;
  Node< T >* head = otherList.head_;
  while (head)
  {
    pushBack(head->data);
    head = head->next;
  }
}

template< typename T >
jirkov::List< T >::List(List&& otherList)
{
  head_ = otherList.head_;
  tail_ = otherList.tail_;
  otherList.head_ = nullptr;
  otherList.tail_ = nullptr;
}

template< typename T >
jirkov::List< T >::~List()
{
  clear();
}

template< typename T >
void jirkov::List< T >::pushFront(const T& data)
{
  Node< T >* node = new Node< T >(data);
  if (head_ != nullptr)
  {
    node->next = head_;
    head_ = node;
  }
  else
  {
    head_ = tail_ = node;
  }
}

template< typename T >
void jirkov::List< T >::pushBack(const T& data)
{
  Node< T >* node = new Node< T >(data);
  if (head_ == nullptr)
  {
    head_ = tail_ = node;
  }
  else
  {
    tail_->next = node;
    tail_ = node;
  }
}

template< typename T >
size_t jirkov::List< T >::getSize()
{
  jirkov::Node< T >* head = head_;
  size_t size = 0ull;
  while (head)
  {
    size++;
    head = head->next;
  }
  return size;
}


template< typename T >
void jirkov::List< T >::popFront()
{
  if (head_ == tail_)
  {
    delete tail_;
    head_ = tail_ = nullptr;
  }
  if (head_ != nullptr)
  {
    Node< T >* node = head_;
    head_ = node->next;
    delete node;
  }
}

template< typename T >
bool jirkov::List< T >::empty()
{
  return head_ == nullptr ? true : false;
}
template< typename T >
void jirkov::List< T >::clear()
{
  while (head_)
  {
    popFront();
  }
}

template< typename T >
void jirkov::List< T >::swap(List< T >& otherList)
{
  jirkov::Node< T >* head = head_;
  head_ = otherList.head_;
  otherList.head_ = head;
  delete head;
  jirkov::Node< T >* tail = tail_;
  tail_ = otherList.tail_;
  otherList.tail_ = tail;
  delete tail;
}

template< typename T >
void jirkov::List< T >::assign(size_t n, const T& value)
{
  for (size_t i = 0; i < n; i++)
  {
    push_back(value);
  }
}

template< typename T >
jirkov::Node< T >* jirkov::List< T >::operator[](const int index)
{
  if (empty() == true)
  {
    return nullptr;
  }
  Node< T >* head = head_;
  for (int i = 0; i < index; i++)
  {
    head = head->next;
    if (!head)
    {
      return nullptr;
    }
  }
  return head;
}

template< typename T >
jirkov::Iterator< T > jirkov::List< T >::begin() const
{
  return Iterator< T >(head_);
}

template< typename T >
jirkov::Iterator< T > jirkov::List< T >::end() const
{
  return Iterator< T >(tail_->next);
}

template< typename T >
const jirkov::Iterator< T > jirkov::List< T >::cbegin() const
{
  return Iterator< T >(head_);
}

template< typename T >
const jirkov::Iterator< T > jirkov::List< T >::cend() const
{
  return Iterator< T >(tail_->next);
}
#endif
