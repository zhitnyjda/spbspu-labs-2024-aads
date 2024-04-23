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
    Node<T>* head_;
    Node<T>* tail_;
    List();
    List(List<T>&& otherList);
    ~List();
    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    bool empty();
    void clear();
    void swap(List<T>& otherList);
    size_t getSize();
    Node<T>* operator[](const int index);
    Iterator<T> begin() const;
    Iterator<T> end() const;
    const Iterator<T> cbegin() const;
    const Iterator<T> cend() const;
  };
}

template< typename T >
jirkov::List< T >::List() :
  head_(nullptr),
  tail_(nullptr)
{}

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
  delete head_;
  delete tail_;
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
#endif
