#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <cassert>
#include <memory>
#include <iostream>

namespace doroshenko
{
  template < typename T >
  class List
  {
  public:
    struct Node
    {
    public:
      friend class List< T >;
      friend class Iterator;
      Node(T value) :
        data(value),
        next(nullptr)
      {}
    private:
      T data;
      Node* next;
    };

    class Iterator
    {
    public:
      friend class List< T >;
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

    private:
      Node* node;
    };

    List();
    List(size_t n, const T& value);
    List(const List< T >& otherList);
    List(List< T >&& otherList);
    ~List();

    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    bool isEmpty();
    void clear();
    void swap(List< T >& otherList);
    void assign(size_t n, const T& value);
    void remove(const T& value);
    template< typename P >
    void removeIf(P p);
    size_t getSize();
    T& front();
    T& back();

    Node* operator[](const int index);

    Iterator begin() const;
    Iterator end() const;

    const Iterator cbegin() const;
    const Iterator cend() const;

  private:
    Node* head_;
    Node* tail_;
  };
}

template< typename T >
doroshenko::List< T >::List() :
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
doroshenko::List< T >::List(size_t n, const T& value)
{
  head_ = nullptr;
  tail_ = nullptr;
  for (size_t i = 0; i < n; i++)
  {
    pushBack(value);
  }
}

template< typename T >
doroshenko::List< T >::List(const List< T >& otherList)
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
doroshenko::List< T >::List(List&& otherList)
{
  head_ = otherList.head_;
  tail_ = otherList.tail_;
  otherList.head_ = nullptr;
  otherList.tail_ = nullptr;
}

template< typename T >
doroshenko::List< T >::~List()
{
  clear();
  delete head_;
  delete tail_;
}

template< typename T >
void doroshenko::List< T >::pushFront(const T& data)
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
void doroshenko::List< T >::pushBack(const T& data)
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
size_t doroshenko::List< T >::getSize()
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
void doroshenko::List< T >::popFront()
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
bool doroshenko::List< T >::isEmpty()
{
  if (head_ == nullptr)
  {
    return true;
  }
  return false;
}

template< typename T >
void doroshenko::List< T >::clear()
{
  while (head_)
  {
    popFront();
  }
}

template< typename T >
void doroshenko::List< T >::swap(List< T >& otherList)
{
  Node* head = otherList.head_;
  Node* tail = otherList.tail_;
  otherList.head_ = head_;
  head_ = head;
  otherList.tail_ = tail_;
  tail_ = tail;
}

template< typename T >
void doroshenko::List< T >::assign(size_t n, const T& value)
{
  for (size_t i = 0; i < n; i++)
  {
    push_back(value);
  }
}

template< typename T >
void doroshenko::List< T >::remove(const T& value)
{
  if (!isEmpty())
  {
    Node* head = head_;
    Node* postHead = head_->next;
    Node* toRemove = nullptr;
    if (head->data == value)
    {
      popFront();
      head = head_;
      postHead = head->next;
    }
    while (postHead)
    {
      if (postHead->data == value)
      {
        if (postHead->next == nullptr)
        {
          delete postHead;
          postHead = nullptr;
          head->next = nullptr;
          tail_ = head;
        }
        else
        {
          toRemove = postHead;
          head->next = postHead->next;
          postHead = head->next;
          delete toRemove;
        }
      }
      else
      {
        head = head->next;
        postHead = head->next;
      }
    }
  }
}

template< typename T >
template< typename P >
void doroshenko::List< T >::removeIf(P p)
{
  if (!isEmpty())
  {
    Node* head = head_;
    Node* postHead = head_->next;
    Node* toRemove = nullptr;
    if (p(head->data))
    {
      popFront();
      head = head_;
      postHead = head->next;
    }
    while (postHead)
    {
      if (p(postHead->data))
      {
        if (postHead->next == nullptr)
        {
          delete postHead;
          postHead = nullptr;
          head->next = nullptr;
          tail_ = head;
        }
        else
        {
          toRemove = postHead;
          head->next = postHead->next;
          postHead = head->next;
          delete toRemove;
        }
      }
      else
      {
        head = head->next;
        postHead = head->next;
      }
    }
  }
}

template< typename T >
T& doroshenko::List< T >::front()
{
  return head_->data;
}

template< typename T >
T& doroshenko::List< T >::back()
{
  return tail_->data;
}

template< typename T >
typename doroshenko::List< T >::Node* doroshenko::List< T >::operator[](const int index)
{
  if (isEmpty() == true)
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

template< typename T >
typename doroshenko::List< T >::Iterator doroshenko::List< T >::begin() const
{
  return Iterator(head_);
}

template< typename T >
typename doroshenko::List< T >::Iterator doroshenko::List< T >::end() const
{
  return Iterator(tail_->next);
}

template< typename T >
const typename doroshenko::List< T >::Iterator doroshenko::List< T >::cbegin() const
{
  return Iterator(head_);
}

template< typename T >
const typename doroshenko::List< T >::Iterator doroshenko::List< T >::cend() const
{
  return Iterator(tail_->next);
}

template< typename T >
doroshenko::List< T >::Iterator::Iterator() :
  node(nullptr)
{}

template< typename T >
doroshenko::List< T >::Iterator::Iterator(Node* pointer) :
  node(pointer)
{}

template< typename T >
typename doroshenko::List< T >::Iterator& doroshenko::List< T >::Iterator::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template< typename T >
typename doroshenko::List< T >::Iterator doroshenko::List< T >::Iterator::operator++(int)
{
  assert(node != nullptr);
  Iterator result(*this);
  ++(*this);
  return result;
}

template< typename T >
T& doroshenko::List< T >::Iterator::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
T* doroshenko::List< T >::Iterator::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< typename T >
bool doroshenko::List< T >::Iterator::operator!=(const Iterator& rhs) const
{
  return !(rhs == *this);
}

template< typename T >
bool doroshenko::List< T >::Iterator::operator==(const Iterator& rhs) const
{
  return node == rhs.node;
}

#endif
