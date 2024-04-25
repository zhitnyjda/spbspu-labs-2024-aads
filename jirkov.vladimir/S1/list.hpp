#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <iostream>
#include <memory>
#include <cassert>

namespace jirkov
{
  template < typename T >
  class List
  {
  public:
    struct Node
    {
      T data;
      Node* next;
      Node(T value) :
        data(value),
        next(nullptr)
      {}
    };
    struct Iterator
    {
      Node* node;
      Iterator();
      ~Iterator() = default;
      Iterator(const Iterator&) = default;
      Iterator& operator= (const Iterator&) = default;
      Iterator(Node* pointer);
      Iterator& operator++();
      Iterator operator++(int);
      T& operator*();
      T* operator->();
      bool operator!=(const Iterator& rhs) const;
      bool operator==(const Iterator& rhs) const;
    };
    Node* head_;
    Node* tail_;
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
    size_t getSize();
    void assign(size_t n, const T& value);
    void remove(const T& value);
    template<typename P>
    void removeIf(P p);
    Node* operator[](const int index);
    Iterator begin() const;
    Iterator end() const;
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
  Node* head = otherList.head_;
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
  Node* node = new Node(data);
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
  Node* node = new Node(data);
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
  Node* head = head_;
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
    Node* node = head_;
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
  Node* head = head_;
  head_ = otherList.head_;
  otherList.head_ = head;
  delete head;
  Node* tail = tail_;
  tail_ = otherList.tail_;
  otherList.tail_ = tail;
  delete tail;
}

template< typename T >
typename jirkov::List< T >::Node* jirkov::List< T >::operator[](const int index)
{
  if (empty() == true)
  {
    return nullptr;
  }
  Node* head = head_;
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
template<typename T>
void jirkov::List< T >::assign(size_t n, const T& value)
{
  for (size_t i = 0; i < n; i++)
  {
    push_back(value);
  }
}
template<typename T>
void jirkov::List<T>::remove(const T& value)
{
  Node* current = head_;
  Node* previous = nullptr;

  while (current != nullptr)
  {
    if (current->data == value)
    {
      if (previous == nullptr)
      {
        popFront();
        current = head_;
      }
      else
      {
        previous->next = current->next;
        if (current->next == nullptr)
        {
          tail_ = previous;
        }
        delete current;
        current = previous->next;
      }
    }
    else
    {
      previous = current;
      current = current->next;
    }
  }
}
template <class T>
template <class P>
void jirkov::List<T>::removeIf(P p) {
  Node* current = head_;
  Node* previous = nullptr;
  while (current)
  {
    if (p(current->data))
    {
      if (previous)
      {
        previous->next = current->next;
      }
      else
      {
        head_ = current->next;
      }
      delete current;
      current = previous ? previous->next : head_;
    }
    else
    {
      previous = current;
      current = current->next;
    }
  }
  if (!head_)
  {
    tail_ = nullptr;
  }
}
template< typename T >
typename jirkov::List< T >::Iterator jirkov::List< T >::begin() const
{
  return Iterator(head_);
}

template< typename T >
typename jirkov::List< T >::Iterator jirkov::List< T >::end() const
{
  return Iterator(tail_->next);
}

template< typename T >
jirkov::List< T >::Iterator::Iterator() :
  node(nullptr)
{}

template< typename T >
jirkov::List< T >::Iterator::Iterator(Node* pointer) :
  node(pointer)
{}

template< typename T >
typename jirkov::List< T >::Iterator& jirkov::List< T >::Iterator::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}
template< typename T >
typename jirkov::List< T >::Iterator jirkov::List< T >::Iterator::operator++(int)
{
  assert(node != nullptr);
  Iterator result(*this);
  ++(*this);
  return result;
}

template< typename T >
T& jirkov::List< T >::Iterator::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
T* jirkov::List< T >::Iterator::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< typename T >
bool jirkov::List< T >::Iterator::operator!=(const Iterator& rhs) const
{
  return node == rhs.node;
}

template< typename T >
bool jirkov::List< T >::Iterator::operator==(const Iterator& rhs) const
{
  return !(rhs == *this);
}
#endif
